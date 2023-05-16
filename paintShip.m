function shipDomainM = paintShip(ax, shipData, color, partten)
%APP_paint_ship 
% ---------paint_ship------------------------------------------
% 函数功能:绘制船舶
% notice：
% input
%   refer           当前参考点经纬度
%   shipData     船舶数据包[1.MMSI 2.X 3.Y 4.cor 5.speed 6.lenth 7.width 8. phi]
%   color           要绘制的船舶的颜色
%--------------------------------------------------------------
% author:wangyan
% date:2021年10月12日
% update:2022年1月14日
% update:2022年5月13日         所有船舶统一颜色
% update:2022年5月26日
% update:2022年6月1日
% update:2022年7月29日
% update:2023年5月15日 改名
%============================================================== 
    shipXY = shipData(2:3);
    
    shipDomainM = cell(1,2);           %存放船舶领域横纵坐标
    shipCorM = cell(1,2);                  %存放船舶航向横纵坐标
    
    if shipData(8) == -1
        shipData(8) = shipData(4);
    end
    %获得船舶/障碍物领域和航向
    [shipDomainM{1, 1},shipDomainM{1,2}] = APP_shipdomain(shipXY, ...
        APP_tran_cor(shipData(8)), shipData(6), shipData(7));
    [shipCorM{1, 1}, shipCorM{1, 2}] = APP_corpaint(shipXY, shipData(6), ...
        APP_tran_cor(shipData(8)));
    
    %% 将墨卡托米转换为经纬度
    
    %%绘制    
    %船舶领域和
    myFill(ax,shipDomainM{1, 1}, shipDomainM{1, 2}, color, partten);
    ax.NextPlot = 'add';
    line(ax,shipCorM{1, 1}, shipCorM{1, 2},'color','black');
    
end
function myFill(ax, DX, DY, color, partten)
% color 颜色
% partten 0 空， 1有线



% 设置等分间距 
delta = 16;
% 画闭合轮廓
plot(ax, [DX, DX(1)], [DY, DY(1)], 'Color', color);
% 根据partten确定图案并绘制
ax.NextPlot = 'add';
if partten == 1 
    % 长边连线
    dx1 = (DX(3)-DX(2))/delta;
    dx2 = (DX(4)-DX(1))/delta;

    dy1 = (DY(3)-DY(2))/delta;
    dy2 = (DY(4)-DY(1))/delta;
    x1 = DX(2);
    y1 = DY(2);
    x2 = DX(1);
    y2 = DY(1);
    for i = 1:delta - 1
        x1 = x1 + dx1;
        y1 = y1 + dy1;
        x2 = x2 + dx2;
        y2 = y2 + dy2;
        plot(ax, [x1, x2], [y1, y2], 'Color', color)
    end
else
    % 网格线
    fill(ax, DX, DY, color, 'edgealpha', 0, 'facealpha', 0.4);
end
    
end
