#ifndef PORTAL_H
#define PORTAL_H

#include <string>
#include <map>

class Hero;  

class Portal {
private:
    std::string m_sourceLocation;
    std::string m_destinationLocation;
    bool m_isLocked;
    std::string m_activationCondition;
    std::string m_riddleAnswer;         
    bool m_isRiddleBased;             
    static std::map<std::string, std::string> m_riddles; 
public:
    Portal(const std::string& source, const std::string& dest, bool locked, 
           const std::string& condition, const std::string& answer = "");
    
    bool attemptActivation(const std::string& playerInput, Hero* hero);
    bool isLocked() const;
    std::string getSource() const;
    std::string getDestination() const;
    std::string getCondition() const;
    bool isRiddleBased() const;
};

#endif // PORTAL_H