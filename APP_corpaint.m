function [CX,CY] = APP_corpaint(pos,lenth,cor)
%APP_CORPAINT 绘制船舶航向
%input
%   pos     船舶当前位置
%   lenth   船舶长度 m
%   cor     船舶航向 度
%output
%   CX      起始点横坐标
%   CY      起始点纵坐标
%----------------------------------------------
%author:wangyan
%date:2022年1月6日
%----------------------------------------------
CX = pos(1);
CX = [CX, pos(1)+lenth*cos(cor/180*pi)];
CY = pos(2);
CY = [CY, pos(2)+lenth*sin(cor/180*pi)];

end