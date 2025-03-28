#include <iostream>
#include <algorithm>  

#include "Portal.h"
#include "Hero.h"

std::map<std::string, std::string> Portal::m_riddles = {
    {"What has keys but can't open locks?", "piano"},
    {"I speak without a mouth and hear without ears. What am I?", "echo"},
    // {"What has a head, a tail, but no body?", "coin"}
};

Portal::Portal(const std::string& source, const std::string& dest, bool locked, 
           const std::string& condition, const std::string& answer) 
           : m_sourceLocation(source), m_destinationLocation(dest), m_isLocked(locked),
             m_activationCondition(condition), m_riddleAnswer(answer), m_isRiddleBased(!answer.empty()) {}

bool Portal::attemptActivation(const std::string& playerInput, Hero* hero) {
    if (!m_isLocked) return true;

    if (m_isRiddleBased) {
        std::string inputLower = playerInput;
        std::string answerLower = m_riddleAnswer;
        std::transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);
        std::transform(answerLower.begin(), answerLower.end(), answerLower.begin(), ::tolower); 

        if (inputLower == answerLower) {
            std::cout << "Correct! The portal activates.\n";
            m_isLocked = false;
            return true;
        } else {
            std::cout << "Incorrect answer. The portal remains locked.\n";
            return false;
        }
    } else {
        for (const std::string& item : hero->getInventory()) {  
            if (item == m_activationCondition) {
                std::cout << "You use the " << m_activationCondition << ". The portal activates!\n";
                m_isLocked = false;
                return true;
            }
        }
        std::cout << "You need a " << m_activationCondition << " to unlock this portal.\n";
        return false;
    }
} 

bool Portal::isLocked() const {
    return m_isLocked;
}

std::string Portal::getSource() const {
    return m_sourceLocation;
}

std::string Portal::getDestination() const {
    return m_destinationLocation;
}

std::string Portal::getCondition() const {
    return m_activationCondition;
}

bool Portal::isRiddleBased() const {
    return m_isRiddleBased;
}
