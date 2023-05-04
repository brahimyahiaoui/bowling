#include "bowling.h"
#include "iostream"

// Last static id initialization
unsigned int CBowler::LastId = 0;

/**
* Construtor of the CFrame Objects
* \param prmFrameNumber Frame number
*/
CFrame::CFrame(unsigned int prmFrameNumber) : m_FrameNumber{ prmFrameNumber }
{
    m_IsFinished = false;
    m_Score = 0u;
    m_NumberOfRolls = 1u;
    m_PreviousFrame = NULL;
    m_Events = new vector<EEvent>();
#ifdef _DEBUG
    cout << "[DEBUG]: Initlisation of the frame " << m_FrameNumber << "." << endl;
#endif // _DEBUG
}

/** Destrutor of the CFrame Objects */
CFrame::~CFrame()
{
    m_Events->clear();
    delete m_Events;
#ifdef _DEBUG
    cout << "[DEBUG]: Destruction of the frame " << m_FrameNumber << "." << endl;
#endif // _DEBUG
}

/** Update previous frames if it's necessary */
void CFrame::UpdatePreviousFrames()
{
    // Four possible cases
    // 1) Case after a strike
    // 2) Case after a spare
    // 3) Case a strike after strike
    // 4) Case a strike after strike after strike
    size_t currentRollNumber = m_Events->size();
    bool addScoreAfterSpare = currentRollNumber == (size_t)1 && m_PreviousFrame->IsSpare();
    bool addScoreAfterStrike = currentRollNumber == (size_t)2 && m_PreviousFrame->IsStrike();
    bool addScoreStrikeAfterStrike = m_PreviousFrame->IsStrike() && IsStrike();
    bool addScoreStrikeAfterStrikeAfterStrike = m_FrameNumber > 1 && m_PreviousFrame->IsStrike() && IsStrike() \
        && m_PreviousFrame->m_PreviousFrame->IsStrike();
    if (addScoreAfterStrike || addScoreAfterSpare || addScoreStrikeAfterStrike)
        m_PreviousFrame->m_Score += m_Score;
    if (addScoreStrikeAfterStrikeAfterStrike)
        m_PreviousFrame->m_PreviousFrame->m_Score += m_Score;
#ifdef _DEBUG
    cout << "[DEBUG]: Updated score for:" << endl << \
        "1) Case after a strike: " << addScoreAfterStrike << endl << \
        "2) Case after a spare: "  << addScoreAfterSpare << endl << \
        "3) Case a strike after strike: " << addScoreStrikeAfterStrike << endl << \
        "4) Case a strike after strike after strike: " << addScoreStrikeAfterStrikeAfterStrike << endl;
#endif // _DEBUG
}

/**
* Check if the frame contains spare event
* \return True if frame spare event
*/
bool CFrame::IsSpare()
{
    // Spare event appears only in the second turn
    if (m_Events->size() >=2)
        return m_Events->at(1) == EEvent::spare;
    return false;
}

/**
* Check if the frame contains strike
* \return True if frame contains strike event
*/
bool CFrame::IsStrike()
{
    // Strike event appears only in the first turn
    if (m_Events->size() >= 1)
        return m_Events->at(0) == EEvent::strike;
    else
        return false;
}

/**
* Calculate score of this frame and eventually update previous frames
* \param prmNumberOfPinsDown Number of pins knocked down
* \return Symbole for the result
*/
char CFrame::ComputeScore(unsigned int prmNumberOfPinsDown)
{
    char val2Return = '\0';

    // First we add all pins knocked down
    m_Score += prmNumberOfPinsDown;

    // Saving the event
    if (prmNumberOfPinsDown == 0)
    {
        m_Events->push_back(EEvent::miss);
        if (m_NumberOfRolls == 1u) m_NumberOfRolls++;
        val2Return = SYMBOL_MISS;
    }
    else if (prmNumberOfPinsDown < (unsigned int)EEvent::numberOfPins && \
        m_Score != (unsigned int)EEvent::numberOfPins)
    {
        m_Events->push_back((EEvent)prmNumberOfPinsDown);
        if (m_NumberOfRolls == 1u) m_NumberOfRolls++;
        val2Return = '0' + (char)prmNumberOfPinsDown;
    }
    else if (m_NumberOfRolls == 2u && m_Score == (unsigned int) EEvent::numberOfPins)
    {
        m_Events->push_back(EEvent::spare);
        if (m_FrameNumber == NBR_OF_FRAME - 1) m_NumberOfRolls++;
        val2Return = SYMBOL_SPARE;
    }
    else if (m_NumberOfRolls == 1u && m_Score == (unsigned int) EEvent::numberOfPins)
    {
        m_Events->push_back(EEvent::strike);
        if (m_FrameNumber == NBR_OF_FRAME - 1) m_NumberOfRolls += 2;
        val2Return = SYMBOL_STRIKE;
    }
    else if (m_NumberOfRolls > 2u)
    { // Bonus for a strike event
        m_Events->push_back(EEvent::strike);
        m_Score += (unsigned int)EEvent::numberOfPins;
        // Next instruction means that last turn in bonus is a strike and score should be 300u
        if (m_Events->size() == (size_t)3) m_Score += (unsigned int)EEvent::numberOfPins;
        val2Return = SYMBOL_STRIKE;
    }
    // We suppose that in this context there is no possibility to have another case

    // Update previous frames (withou including the bonus to stay always in same frame)
    if (m_PreviousFrame && m_NumberOfRolls <= 2u) UpdatePreviousFrames();

    // Test if this frame is finished
    m_IsFinished = m_NumberOfRolls == (unsigned int)m_Events->size();

    return val2Return;
}

/**
* Construtor of the CFrame Objects
* \param prmName Bowler name
*/
CBowler::CBowler(string prmName) : m_Name{ prmName }
{
    // Here we generate new Id and initialize all frames
    m_LineResult = "";
    m_Id = LastId++;
#ifdef _DEBUG
    cout << "[DEBUG]: Initlisation of the bowler " << m_Name << " with id " << m_Id << "." << endl;
#endif // _DEBUG
    m_Frames = new list<CFrame*>();
    for (int i = 0; i < NBR_OF_FRAME; i++)
        m_Frames->push_back(new CFrame(i));
    m_CurrentFrame = m_Frames->begin();
}

/** Destrutor of the CFrame Objects */
CBowler::~CBowler()
{
    m_Frames->clear();
    delete m_Frames;
#ifdef _DEBUG
    cout << "[DEBUG]: Destruction of the bowler " << m_Name << " with id " << m_Id << "." << endl;
#endif // _DEBUG
}

unsigned int CBowler::CalculateLastScore()
{
    unsigned int score = 0;
    for (auto it = m_Frames->begin(); it != m_Frames->end() ; it++)
        score += (*it)->GetScore();
    return score;
}

/**
* Compute last knocked pins
* \param prmNumberOfPinsDown Number of pins knocked down
*/
void CBowler::ComputeLastLaunch(unsigned int prmNumberOfPinsDown)
{
    if (m_CurrentFrame == m_Frames->end())
    {
        cout << "[INFO]: Game is finished." << endl;
    }
    else
    {
        // Here results ar built
        if (prmNumberOfPinsDown <= (unsigned int)EEvent::numberOfPins)
        {
            // We set previous only if we need it to compute a roll after a strike or a spare 
            CFrame* previousFrame = NULL;
            m_LineResult += (*m_CurrentFrame)->ComputeScore(prmNumberOfPinsDown);
            if ((*m_CurrentFrame)->IsSpare() || (*m_CurrentFrame)->IsStrike()) previousFrame = *m_CurrentFrame;
            if ((*m_CurrentFrame)->IsFinished()) m_CurrentFrame++; // Frame is finished
            if (m_CurrentFrame != m_Frames->end()) (*m_CurrentFrame)->SetPreviousFrame(previousFrame);
            cout << "[INFO]: The " << m_Name << " score is " << m_LineResult << endl;
        }
        else
            cout << "[ERROR]: Please enter a valide number of pins (between 0 and 10).";
    }
}
