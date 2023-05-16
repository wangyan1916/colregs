
function Tc = distanceTinv(refer, in)
%DISTANCET
%   距离投影逆过程，以某一点refer为原点, 获得in相对refer点横纵坐标米的经纬度
%   input
% refer     参照点经纬度坐标，单位，度
% in        待求点（列表）经纬度坐标，单位度

refer = refer./180*pi;
% in = in./180*pi;

a = 6378137;    % 长轴
b = 6356752;    % 短轴
e = (a*a-b*b)/(a*a);    %第一偏心率
M = (a*(1-e))/(sqrt(1-e*sin(refer(2))*sin(refer(2))))^3;       % 子午圈曲率半径
N = a/(sqrt(1-e*sin(refer(2)*sin(refer(2)))));              % 卯酉圈曲率半径
rLat = N*cos(refer(2));                                     % 纬线圈半径

num = size(in, 1);
Tc = zeros(num, 2);
for i = 1: num
    Tc(i, 1) = in(i, 1)/rLat + refer(1);
    Tc(i, 2) = in(i, 2)/M + refer(2);
end
Tc = Tc./pi*180;
end