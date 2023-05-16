//
// Created by rocky on 2023/5/15.
//

#ifndef TESTCOLREGS_COLREGS_HPP
#define TESTCOLREGS_COLREGS_HPP
#include <vector>
namespace COLREGs {
    struct ship
    {
    private:
        std::vector<double> shipInfo;
        double x, y, spe, cor;
    public:
        /**
         * @brief 船舶数据接口，将船舶信息拆分，角度进行转换
         * @param shipInfo_ [0]MMSI(0时为静态障碍物) [1]x坐标m [2]y坐标m [3]航向 度 [4]航速 节 [5]船长 m [6]船宽 m [7]艏向 度
         */
        explicit ship(const std::vector<double> &shipInfo_);
        double getX() const;
        double getY() const;
        double getSpe() const;
        double getCor() const;

    };
    class Zheng {
    private:
        ship* ourShip;
        ship* targetShip;

        /**
         * @brief 他船相对于本船的真方位
         * @return 角度（度）
         */
        double getAT();
        /**
         * @brief 本船相对于他船的真方位
         * @return
         */
        double getAO();

        /**
         * @brief 角度标准化到0-360
         * @param deg_
         * @return
         */
        static double angleNormalization(double deg_);
        /**
         * @brief 弧度转角度并转为航海角度
         * @param rad_
         * @return 以正北为0，顺时针的角度
         */static double rad2deg(double rad_);
    public:
        enum MeetingType
        {
            CROSS,
            HEAD_ON,
            OVERTAKE,
        };
        /**
         * @brief 根据郑中义论文中判断避碰责任与转向方向
         * @param shipsInfo
         * @return 布尔容器，第一个值是是否有责任，第二个值是是否右转，否为左转
         */
        Zheng(const std::vector<std::vector<double>> &shipsInfo);
        /**
         * @brief 获得两个布尔值，第一个确定有无避碰责任，第二确定右转还是左转
         * @return
         */
        std::vector<bool> getResult();
        /**
         * @brief 获得会遇场景
         * @return
         */
        MeetingType getEncounter();
    private:
        MeetingType encounter;
    };

} // COLREGs

#endif //TESTCOLREGS_COLREGS_HPP
