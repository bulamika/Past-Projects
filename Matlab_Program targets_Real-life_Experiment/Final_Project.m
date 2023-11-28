function Final_Project
%The final project contains two subfunctions for the purpose of the study.
%
%First subfunction contains an experimental script, showcasing two faces at
%a time. Participants will be asked to rate how different the right face is
%from the left face based on age and attractiveness. The
%difference/disimilarity matrix from the experiment will be recorded 
%during the expriement (subfunction one) and analysed by metric MDS technique
%from the second subfunction.
%
%Second subfunction contains a metric MDS analyses; the analyses help us to
%visualize how individuals differentiate faces differently based on attrativeness
% and age. Differences between faces will be visualized based on q eigenvalues
%dimensional map.
%
%By running this function, both experiment and analysis script will be
%ran. The user can also run these functions seperately.
%
%                            Mingjia Chen, April 2023

%% Experimental script
%reduced number of faces (n=4) for demo
face_rating_attract();  %rate faces based on attractiveness
face_rating_age(); %rate faces based on age

%% Analysis of data set
mMDS();

end

