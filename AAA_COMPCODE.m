%%%%%%%%%%%%%%%%%%%%%%%%%%
% Nico Scialdone, Kin Blandford, Talon Rencher
% u####'s
% ME EN 1010 Lab Section 002
% Competition Code
% 4/19/2022
%%%%%%%%%%%%%%%%%%%%%%%%%%
clear, clc, close all

%PRE LAUNCH LIST:
%Check port number, image file name, data file names for proj and linkage
%Adjust stripe nums and xTarget by specified amount if needed
%Arduino change reload angle

%% Calibration Stuff

load('L_vector.mat');
load('d_vector.mat');
load('H_vector.mat');

linkage_filename = 'Comp_Robot3_LinkageData.xlsx';
projectile_filename = 'Comp_Robot3_ProjectileData.xlsx';

% Linkage

[thetaS, thetaL_avg] = LinkageData(linkage_filename);

[optimalParams, SSE] = fminsearch(@CompareLinkageData,[40.0,0.015,11.7],[], L, thetaS, thetaL_avg);

%figure

%LinkageData(linkage_filename);

%hold on

%ThetaLaunch(L,thetaS,optimalParams);

%legend('experiment','theory','Location','southeast');

%graphText1 = sprintf(' alpha = %.4f degrees \n beta = %.4f \n thetaL0 = %4.4f degrees \n SSE = %.4f \n', optimalParams(1),optimalParams(2),optimalParams(3),SSE);

%text(40,40,graphText1);

% Projectile

[thetaL, aveDist] = ProjectileData(projectile_filename);
[optimalVelCoeffs, SSE] = fminsearch(@CompareProjectileData,[3.2,0],[],d,thetaL,aveDist);

%figure

%ProjectileData(projectile_filename);

%hold on

%LandingDistance(d,optimalVelCoeffs,thetaL);

%legend('experiment','theory');

%graphText2 = sprintf('The SSE is %.4f for kappa = %.4f m/s and greekL = %.4f \n',SSE,optimalVelCoeffs(1),optimalVelCoeffs(2));
%text(30,.4,graphText2);

%% Image Processing / Target Finding

imageArray = imread('S22_CP_B2.bmp');
disp("Click on the peashooter to get color information")

[clickedRGB] = ColorPicker(imageArray)
Rtarget = 5*clickedRGB(3)
Gtarget = 5*clickedRGB(3)
Btarget = 4*clickedRGB(3)
targetRGB = [Rtarget,Gtarget,Btarget];

[centroidRowVec, centroidColVec, imageArray] = FindAllTargetCentroids(imageArray,targetRGB);

image(imageArray)
axis image
hold on
drawnow

plot(centroidColVec,centroidRowVec,'xw');

stripeNum = (0.2.*centroidRowVec)./10
xTarget_m = (650+(0.2.*centroidColVec))./1000

% adjustX = 0 %if shooting long, adjust is negative
% adjustStripe = 0 %if shooting right, adjust is negative
% xTarget_m = xTarget_m + adjustX
% stripeNum = stripeNum + adjustStripe

NumsNTargets = [stripeNum', xTarget_m']

NumsNTargetsSorted = sortrows(NumsNTargets,1)

NumsNTargetsMin = NumsNTargetsSorted(2,:)

NumsNTargetsSorted(2,:) = []

NumsNTargetsSorted = [NumsNTargetsSorted; NumsNTargetsMin]

stripeNum1 = NumsNTargetsSorted(:,1)'

xTarget_m1 = NumsNTargetsSorted(:,2)'

%% Talking to Romeo

% serial communication setup
RomeoCOM = serialport('/dev/cu.usbmodem14101',9600); %/dev/cu.usbmodem14101 %COM3
endCheck = "done";
dataCheck = "ready for data";

% key press detection setup
kbhit('init');
key = char(0);
prevKey = key;

while(1)
    % key press detection
    prevKey = key;
    key = kbhit;
    pause(1/6000)
    if key == 'q'
        disp('ABORTING')
        break
    elseif key ~= char(0)
        disp('sending letter to Arduino')
        writeline(RomeoCOM,key)
    end

    % serial communication
    if RomeoCOM.NumBytesAvailable > 0
        message = readline(RomeoCOM);
        message = erase(message,sprintf('\r'));
        %break if romeo Serial.println("done");
        if strcmp(message,endCheck) == 1
            break

        elseif strcmp(message,dataCheck) == 1
            %send target info to romeo
            disp("sending data to romeo")
            for target = 1 : 6
                data1 = sprintf('%d',stripeNum1(target));
                writeline(RomeoCOM,data1);
                data2 = sprintf('%.4f',xTarget_m1(target));
                writeline(RomeoCOM,data2);
                %recieve messages back
                message = readline(RomeoCOM);
                message = erase(message,sprintf('\r'));
                disp(message);
            end
            % send linkage parameters to Romeo
            for param = 1 : 3
                paramToSend = sprintf('%.3f',optimalParams(param));
                writeline(RomeoCOM,paramToSend);
            end
            message = readline(RomeoCOM);
            message = erase(message,sprintf('\r'));
            disp(message);
            % send velocity coefficients to Romeo
            for coeff = 1 : 2
                coeffToSend = sprintf('%.4f',optimalVelCoeffs(coeff));
                writeline(RomeoCOM,coeffToSend);
            end
            message = readline(RomeoCOM);
            message = erase(message,sprintf('\r'));
            disp(message);

        else
            disp(message)
        end
    end
end

clear RomeoCOM
kbhit('stop');