function [DX,DY] = APP_shipdomain(pos,phi,lenth,width)
%APP_shipdomain 计算长方形船舶领域
%input
%   pos         当前船舶位置
%   phi         船艏向  度
%   lenth       船舶长度 m
%   width       船舶宽度 m
%output
%   DX          船舶领域横坐标[左上 右上 右下 左下]
%   DY          船舶领域纵坐标
%---------------------------------------
%author:wangyan
%date:2022年1月6日
%---------------------------------------
phi = phi/180*pi;


xfm = lenth/2*cos(phi);     %相对于船舶中心，船艏边界中点横纵坐标
yfm = lenth/2*sin(phi);

xam = lenth/2*cos(pi+phi);  %相对于船舶中心，船尾边界中点横纵坐标
yam = lenth/2*sin(pi+phi);

xl = width/2*cos(phi+pi/2);    %相对于中点，左舷点偏移量
yl = width/2*sin(phi+pi/2);


xr = width/2*cos(phi+1.5*pi);  %相对于中点，右舷点偏移量
yr = width/2*sin(phi+1.5*pi);


%左上
pxfl = pos(1)+xfm+xl;
pyfl = pos(2)+yfm+yl;


%右上
pxfr = pos(1)+xfm+xr;
pyfr = pos(2)+yfm+yr;

%右下
pxar = pos(1)+xam+xr;
pyar = pos(2)+yam+yr;

%左下
pxal = pos(1)+xam+xl;
pyal = pos(2)+yam+yl;

DX = [pxfl, pxfr, pxar, pxal];
DY = [pyfl, pyfr, pyar, pyal];

end