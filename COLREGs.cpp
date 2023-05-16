//
// Created by rocky on 2023/5/15.
//

#include <cmath>
#include "COLREGs.hpp"

namespace COLREGs {
    ship::ship(const std::vector<double> &shipInfo_) {
        x = shipInfo_.at(1);
        y = shipInfo_.at(2);
        cor = shipInfo_.at(3);
        spe = shipInfo_.at(4);
    }

    double ship::getX() const {
        return x;
    }

    double ship::getY() const {
        return y;
    }

    double ship::getSpe() const {
        return spe;
    }

    double ship::getCor() const {
        return cor;
    }

    Zheng::Zheng(const std::vector<std::vector<double>> &shipsInfo) {
        ourShip = new ship(shipsInfo.at(0));
        targetShip = new ship(shipsInfo.at(1));

    }

    std::vector<bool> Zheng::getResult() {
        std::vector<bool> rel(2, false);
        double tPhi = targetShip->getCor();
        double oPhi = ourShip->getCor();
        double CT = tPhi - oPhi; // 航向交角
// 以我船为中心判断
        double ca = angleNormalization(getAT() - oPhi); //他船相对于我船的弦角
        if(ca <= 5 && ca >= 0) {
            rel[0] = true;
            rel[1] = true;
            if (fabs(180 - fabs(CT)) <= 5) {
                encounter = HEAD_ON;      // (1) 对遇，让路，右转
            } else {
                encounter = CROSS;       // (2) 交叉，让路，右转
            }
        }
        if (ca > 5 && ca <= 67.5)
            if (fabs(180 - fabs(CT)) > 5)
            {
                rel[0] = true;
                rel[1] = true;
                encounter = CROSS;      // (3) 交叉，让路，右转
            }
        if (ca > 67.5 && ca <= 112.5)
            if (fabs(180 - fabs(CT)) > 5)
            {
                rel[0] = true;
                rel[1] = false;
                encounter = CROSS;      // (4) 交叉，让路，左转
            }
        if (ca > 112.5 && ca < 247.5)
        {
            // 应该再考虑速度吗
            rel[0] = false;
            encounter = OVERTAKE;       // (5)被追越，直航
        }
        if (ca > 247.5 && ca <355)
            if (fabs(180 - fabs(CT)) > 5)
            {
                rel[0] = false;
                encounter = CROSS;      // (6) 交叉，直航
            }
        if (ca > 355 && ca < 360)
            if (fabs(180 - fabs(CT)) <= 5) {
                rel[0] = true;
                rel[1] = true;
                encounter = HEAD_ON;      // (7) 对遇，让路，右转
            }else
            {
                rel[0] = true;
                rel[1] = true;
                encounter = CROSS;      // (8) 交叉，让路，右转
            }
// 以他船为中心判断 / 存在一些问题
        double caT = angleNormalization(getAO() - tPhi);
        if (fabs(CT) < 67.5)
        {
            if (caT >= 112.5 && caT <= 180)
            {
                rel[0] = true;
                rel[1] = true;
                encounter = OVERTAKE;  // (9 - 10) 追越，让路，右转
            }else if(caT > 180 && caT <= 210)
            {
                rel[0] = true;
                rel[1] = false;
                encounter = OVERTAKE;  // (11 -12) 追越，让路，左转
            }else if(caT > 210 && caT <= 247.5)
            {
                rel[0] = true;
                rel[1] = false;
                encounter = OVERTAKE;  // (11 -12) 追越，让路，左转
            }
        }

        return rel;
    }

    double Zheng::rad2deg(double rad_) {
        double deg = rad_/M_PI*180;
        if (deg < 0)
            deg += 360;
        if (deg < 90)
            return 90 - deg;
        else
            return 450 - deg;
    }

    double Zheng::getAT() {
        double theta_ = atan2(targetShip->getY() - ourShip->getY(),
                              targetShip->getX() - ourShip->getX());

        return rad2deg(theta_);
    }

    double Zheng::getAO() {
        double theta_ = atan2(ourShip->getY() - targetShip->getY(),
                              ourShip->getX() - targetShip->getX());

        return rad2deg(theta_);
    }

    double Zheng::angleNormalization(double deg_) {
        while(deg_ < 0 || deg_ > 360)
        {
            if (deg_ < 0)
                deg_ += 360;
            else
                deg_ -= 360;
        }
        return deg_;
    }

    Zheng::MeetingType Zheng::getEncounter() {
        return encounter;
    }
} // COLREGs