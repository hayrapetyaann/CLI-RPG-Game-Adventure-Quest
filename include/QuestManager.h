#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include <string>
#include <vector>

#include "Hero.h"

class Quest {
public:
    std::string m_description;
    bool m_isCompleted;
    std::string m_reward;
    int m_xpReward;
};

class QuestManager {
private:
    std::vector<Quest> m_quests;
public:
    void addQuest(const std::string& desc, const std::string& reward, int xp);
    void completeQuest(int index, Hero* hero);
    void displayQuests() const;
};

#endif // QUESTMANAGER_H