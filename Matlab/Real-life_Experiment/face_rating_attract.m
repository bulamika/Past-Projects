%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%the first subfunction-a
function face_rating_attract
% psychtoolbox function to showcase two faces at a time and ask the
% participants to rate how different the right face is comparing to the 
% left one based on distinctiveness and attractiveness. 
% The rating will be used for analyses afterwards.

% Only three faces will be included for demostration purpose, one can
% change variable n to include more faces.

%%%clear the command window and workspace to setup the 
%%%psychtoolbox for a new screen with a white background
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% base
clear;clc;
commandwindow;

BLACK = [0 0 0]; 
WHITE = [255 255 255]; 

% Skip the initial VBL sync tests
Screen('Preference','SkipSyncTests', 1);

screens = Screen('Screens');
screenNumber = max(screens);
[win,winRect] = Screen('OpenWindow',screenNumber, WHITE);

% Get the center coordinates
[Xo, Yo] = RectCenter(winRect);

%%%introductions and instructions of the study
%%%participants are required to press enter to start
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Screen('TextFont', win, 'Arial');
Screen('TextSize', win, 100);
welcome = 'Welcome to the Study';
DrawFormattedText(win, welcome,'center', Yo - 180, BLACK); 

Screen('TextFont', win, 'Arial');
Screen('TextSize', win, 30);
instruction1 = 'Please compare two faces and rate how the face on the right is different';
DrawFormattedText(win, instruction1,'center', 'center', BLACK); 

Screen('TextFont', win, 'Arial');
Screen('TextSize', win, 40);
instruction2 = 'based on Attractiveness';
DrawFormattedText(win, instruction2,'center', Yo + 75, BLACK); 

Screen('TextFont', win, 'Arial');
Screen('TextSize', win, 20);
instruction3 = 'Press the number key to rate from 1 to 7';
DrawFormattedText(win, instruction3,'center', Yo + 120, BLACK); 

Screen('TextFont', win, 'Arial');
Screen('TextSize', win, 20);
instruction4 = '1- very similar    4- neutural     7- very different ';
DrawFormattedText(win, instruction4,'center', Yo + 150, BLACK); 

Screen('TextFont', win, 'Arial');
Screen('TextSize', win, 20);
instruction5 = 'Press 1-7 only:  the study will not continue otherwise';
DrawFormattedText(win, instruction5,'center', Yo + 180, BLACK); 

Screen('TextFont', win, 'Arial');
Screen('TextSize', win, 50);
start = 'Press enter to start.';
DrawFormattedText(win, start,'center', Yo + 400, BLACK); 

Screen('Flip', win);

correctKey = KbName('return');
%press enter to start
while true
	[keyIsDown, secs, keyCode] = KbCheck();
	if keyIsDown && keyCode(correctKey)==1
        WaitSecs(1);
        break
	end
end

% calculation question to make sure they pays attention in the experiment
Screen('TextFont', win, 'Arial');
Screen('TextSize', win, 50);
start = 'Type the answer: how attractive 7-4 = ?';
DrawFormattedText(win, start,'center','center', BLACK); 

Screen('Flip', win);

correctKey = KbName('3#');
%press the correct answer to start
while true
	[keyIsDown, secs, keyCode] = KbCheck();
	if keyIsDown && keyCode(correctKey)==1
        WaitSecs(1);
        break
	end
end

%%%Initialize the faces to display on screen
%%%load the face set (from the lecture)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
load('stim_mat_gray.mat', 'im_mat_gray')

%we will only go through 4 faces (7 pairs) for
%demonstration
n = 4; %size(im_mat_gray,3) %the whole dataset

data_matrix = zeros(n,n);

%assign two positions for the faces
posi1 = [Xo-760, Yo-310, Xo-220, Yo+300];
posi2 = [Xo+220, Yo-310, Xo+760, Yo+300];

Key1 = KbName('1!');
Key7 = KbName('7&');

%%%Actually showing the simulus
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for i = 2:n
    for j = 1:i-1
        %place the i-th and j-th face at the same time on screen
        face1 = Screen('MakeTexture',win,im_mat_gray(:,:,i));
        face2 = Screen('MakeTexture',win,im_mat_gray(:,:,j));
        Screen('DrawTexture', win, face1,[], posi1);
        Screen('DrawTexture', win, face2,[], posi2);

        Screen('Flip', win);
            
        while true
            [keyIsDown, secs, keyCode] = KbCheck();
           %if a key is pushed and the key pressed is a number between 1-7
           if keyIsDown && find(keyCode) >= Key1 && find(keyCode) <= Key7
           %otherwise stimulus will still be presented
           %record the input into ith row and jth column at the matrix
           %and write the matrix into mat at the end for analysis
                data_matrix(i,j) = find(keyCode)-49 + 1; %record it in the matrix (key 1 starts with 49)
                break
           end
        end
        %remove the faces for showing another set
         Screen('FillRect', win, WHITE, winRect);
         Screen('Flip', win);
         WaitSecs(2);
    end
end

%%%closing with a thank you note
%%% and then write the matrix into text file for
%%% further analysis 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Screen('TextFont', win, 'Arial');
Screen('TextSize', win, 50);
thanks = 'Good job!';
DrawFormattedText(win, thanks,'center', 'center', BLACK); 
Screen('Flip', win);

WaitSecs(5);
% close
Screen('CloseAll')

%write the file 
writematrix(data_matrix, 'attract_matrix.txt') 

end