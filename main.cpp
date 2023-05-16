//
// Created by rocky on 2023/5/15.
//
#include <iostream>
#include "COLREGs.hpp"
int main(int argc, char *argv[])
{
    std::vector<std::vector<double>> shipsInfo = {
            {413773475, 1344.26659292599, 1607.30448604533, 73.1, 5.5, 110, 19, 73.1},
            {413839828, 967.098268291974, 1108.48585244496, 58.4, 7.8, 130, 16, 36.8}
    };
    COLREGs::Zheng judge(shipsInfo);
    std::vector<bool> rel = judge.getResult();
    std::string encounter;
    switch (judge.getEncounter()) {
        case COLREGs::Zheng::MeetingType::OVERTAKE:
            encounter = "over take";
            break;
        case COLREGs::Zheng::MeetingType::HEAD_ON:
            encounter = "head on";
            break;
        case COLREGs::Zheng::MeetingType::CROSS:
            encounter = "cross";
            break;
        default:
            encounter = "null";
            break;
    }

    std::cout << "has the duty:" << rel.at(0)<<  std::endl;
    std::cout << "turn right:" << rel.at(1) << std::endl;
    std::cout << "encounter:" << encounter << std::endl;
    return 0;
}