#include <iostream>

#include "QuestManager.h"

void QuestManager::addQuest(const std::string& desc, const std::string& reward, int xp) {
    m_quests.push_back({desc, false, reward, xp});
    std::cout << "Quest Accepted: " << desc << "\n";
}

void QuestManager::completeQuest(int index, Hero* hero) {
    if (index >= 0 && index < m_quests.size() && !m_quests[index].m_isCompleted) {
        m_quests[index].m_isCompleted = true;
        hero->addItem(m_quests[index].m_reward);
        hero->gainXP(m_quests[index].m_xpReward);
        std::cout << "Quest Completed: " << m_quests[index].m_description << "\n";
    }
}

void QuestManager::displayQuests() const {
    std::cout << "Active Quests:\n";
    for (size_t i = 0; i < m_quests.size(); ++i) {
        if (!m_quests[i].m_isCompleted) {
            std::cout << i + 1 << ". " << m_quests[i].m_description << "\n";
        }
    }
}