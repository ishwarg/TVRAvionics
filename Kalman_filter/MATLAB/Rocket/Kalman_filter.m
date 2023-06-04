%Kalman filter test

clf; clc;

%constants
timeStep = 1;
initialPos = 0; 
InitialVel = 0;
x = [initialPos; InitialVel];

initialPosError = 0.1;
initialVelError = 0.0002;

P = [initialPosError 0; 0 initialVelError];

F = [1 timeStep; 0 1];
G = [timeStep^2/2; timeStep];

stateLOG = zeros(170,2);
KnLOG = zeros(170,2);

%calibration

Data = readmatrix('TestData14.xlsx');
aCalibration = Data(1:20,1);
pvCalibration(:,1) = Data(1:20,3);
pvCalibration(:,2) = Data(1:20,2);

%measurmentError = pvCalibration - (ones(20,20)*pvCalibration)*(1/20);

R = (transpose(pvCalibration)*pvCalibration)/19;

pvDeviation(:,1) = aCalibration*timeStep^2/2;
pvDeviation(:,2) = aCalibration*timeStep;

%processError = pvDeviation - (ones(20,20)*pvDeviation)*(1/20);

Q = (transpose(pvDeviation)*pvDeviation)/19;

%simulation

ACCdata = Data(:,1);
GPSdata(:,1) = Data(:,3);
GPSdata(:,2) = Data(:,2);

imax = 200;
iCalibration = 20;

for i = iCalibration:imax + 1
    
    %prediction

    xn = F*x + G*ACCdata(i,1);
    Pn = F*P*transpose(F)+Q;

    %correction/update
    
    Kn = Pn*((Pn + R)^-1);
    x = xn + Kn*(transpose(GPSdata(i,:))-xn);
    P = (eye(2,2) - Kn)*Pn*transpose(eye(2) - Kn)+Kn*R*transpose(Kn);

    %log data
    stateLOG(i,1) = x(1,1);
    stateLOG(i,2) = x(2,1);
    KnLOG(i,1) = Kn(1,1);
    KnLOG(i,2) = Kn(2,2);
    
end

% Calculate error from actual state
RealState = readmatrix('RealPositionData.xlsx');
State(:,1) = RealState(:,2);
State(:,2) = RealState(:,1);
CorrectedError = stateLOG - State;
RawError = GPSdata - State;

ErrorCovarience = transpose(CorrectedError)*CorrectedError/180;
StdevPos = sqrt(ErrorCovarience(1,1));
StdevVel = sqrt(ErrorCovarience(2,2));

% Plot

pt = iCalibration:1:imax;

figure(1); plot(pt,stateLOG(iCalibration:imax,1),'k'); hold on; plot(pt,GPSdata(iCalibration:imax,1),'r'); hold off; 
figure(2); plot(pt,stateLOG(iCalibration:imax,2),'k'); hold on; plot(pt,GPSdata(iCalibration:imax,2),'r'); hold off;
figure(3); plot(pt,ACCdata(iCalibration:imax,:),'r');
figure(4); plot(pt,KnLOG(iCalibration:imax,1),'r'); hold on; plot(pt,KnLOG(iCalibration:imax,2),'g'); hold off;
figure(5); plot(pt,CorrectedError(iCalibration:imax,2),'k'); hold on; plot(pt,RawError(iCalibration:imax,2),'r'); hold off;
figure(6); plot(pt,CorrectedError(iCalibration:imax,1),'k'); hold on; plot(pt,RawError(iCalibration:imax,1),'r'); hold off;
