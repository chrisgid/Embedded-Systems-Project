% %Read in values from file
% fileID = fopen('sweep_data.txt','r');
% filecont = fscanf(fileID,'%f\n');
% fclose(fileID);
% 
% 
% scanpoints = filecont(1); %Get number of scan points, 1st line of file
% scandegrees = filecont(2); %Get range in degrees of scan
% scandata = filecont([3:end]);   %Get scan data, rest of file
% scanXVals = zeros(1, scanpoints); %Initialse XVals for radar
% scanYVals = zeros(1, scanpoints); %Initialse YVals for radar
% 
% scanAngle = scandegrees/scanpoints; %Calculate degrees between scans
% 
% angle = 90 - scandegrees/2; %Calculate start angle of scan
% 
% for i = drange(1:scanpoints)
%     [scanXVals(i), scanYVals(i)] = angletovector(scandata(i), angle);
%     angle = angle + scanAngle;
% end
% 
% 
% radarfig = figure;
% radar = compass(scanXVals, scanYVals,'g');
% radarfig.Name = 'Plot of Scan Sweep';
% radarfig.NumberTitle = 'off';
% radarfig.MenuBar = 'none';
% axis([-inf inf 0 inf]);
% axis fill;
% xlabel('Degrees');
% ylabel('Distance (cm)');
% set(gcf, 'Color',[0.8,0.8,0.8]);
% drawnow;

while true
    %Read in values from file
    fileID = fopen('sweep_data.txt','r');
    filecont = fscanf(fileID,'%f\n');
    fclose(fileID);
    
    
    scanpoints = filecont(1); %Get number of scan points, 1st line of file
    scandegrees = filecont(2); %Get range in degrees of scan
    scandata = filecont([3:end]);   %Get scan data, rest of file
    scanXVals = zeros(1, scanpoints); %Initialse XVals for radar
    scanYVals = zeros(1, scanpoints); %Initialse YVals for radar
    
    scanAngle = scandegrees/scanpoints; %Calculate degrees between scans
    
    angle = 90 - scandegrees/2; %Calculate start angle of scan
    
    for i = drange(1:scanpoints)
        [scanXVals(i), scanYVals(i)] = angletovector(scandata(i), angle);
        angle = angle + scanAngle;
    end
   
    
    close all;
    radarfig = figure;
    radar = compass(scanXVals, scanYVals,'g');
    radarfig.Name = 'Plot of Scan Sweep';
    radarfig.NumberTitle = 'off';
    radarfig.MenuBar = 'none';
    axis([-inf inf 0 inf]);
    axis fill;
    xlabel('Degrees');
    ylabel('Distance (cm)');
    set(gcf, 'Color',[0.8,0.8,0.8]);
    drawnow;
    pause(1);
end
