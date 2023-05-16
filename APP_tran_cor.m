function [cor] = APP_tran_cor(cor_ori,flag)
%APP_TRAN_COR 将航向坐标系进行转换，
%   当flag为1时
%将以正北为正向，顺时针转动变为以正东为正向，逆时针转动的坐标系,对角度进行变换，便于画图
%   当flag为0时
%逆变换,对角度进行变换，便于画图
%flag缺省值为1
%
%author:wangyan
%date：2021年10月11日

if nargin == 1
    flag = 1;
end

if flag == 1
    if cor_ori < 90
        cor = 90 - cor_ori;
    else
        cor = 450 - cor_ori;
    end
elseif flag == 0
    if cor_ori < 90
        cor = 90 - cor_ori;
    else
        cor = 450 - cor_ori;
    end
end

