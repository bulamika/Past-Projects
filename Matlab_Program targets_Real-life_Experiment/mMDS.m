%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%the second subfunction
function mMDS
% After the experimental script, we use the data matrix recorded for analysis.

%%% loading the data
dta = readmatrix('attract_matrix.txt');
dtb = readmatrix('age_matrix.txt');
dt_n = size(dta, 1);

%%% Analysis
%%% mMDS analysis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% metric MDS is used for this particular study. Due to the fact that we
% collect the difference (distance) between sets of faces based on two dimensions
% age and attractiveness, we are confident to say that the data 
% matrix contains pairwise ('approximately' Euclidean) distances suitable 
% for mMDS analysis.

%In this section of the study, we will visualize the first two dimensions
%by conducting a q eigenvalues dimensional map to see the distances between
%faces. An additional PVE histogram will also be constructed to see how
%many percentage of variances each dimension explain. After obtaining the
%visualization for both of the matrices, we averges those two coordinates
%to see how visualization could be if they equally influence each other by
%assumption.

%The result of mMDS analysis can also help to reconstruct original data.

%%% for showcasing the figures, as long as you close one figure, the two
%%% new figures for next matrix will appear, vice versa

%% data a: attractiveness
[PVEa,Ya] = analysis(dta);
%%% MDS PVE diagram
figure
pareto(PVEa)
title('Metric MDS PVE diagram: attrativeness')
xlabel('Dimension')
ylabel('Percent Variance Explained (%)')

%%% Metric MDS q-dimensional Map
figure
plot (Ya(:,1), Ya(:,2), '*')
title('Metric MDS q-dimensional Map:attractiveness')
nm_mat=1:dt_n;
gname(nm_mat)


%% data b: age
[PVEb,Yb] = analysis(dtb);
%%% MDS PVE diagram
figure
pareto(PVEb)
title('Metric MDS PVE diagram: age')
xlabel('Dimension')
ylabel('Percent Variance Explained (%)')

%%% Metric MDS q-dimensional Map
figure
plot (Yb(:,1), Yb(:,2), '*')
title('Metric MDS q-dimensional Map: age')
gname(nm_mat)

%% Combination
%%% Averaging two distance matrices to see how age and attractive 
%%% can influence the visualization togethor.
dt = (dta + dtb)./2;
[PVE,Y] = analysis(dt);

%%% MDS PVE diagram
figure
pareto(PVE)
title('Metric MDS PVE diagram: attractiveness and age')
xlabel('Dimension')
ylabel('Percent Variance Explained (%)')
%%% Metric MDS q-dimensional Map
figure
plot (Y(:,1), Y(:,2), '*')
title('Metric MDS q-dimensional Map: attractiveness and age')
gname(nm_mat)

end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%helper subfunction for calculating PVE and Y
function [PVE, Y] = analysis (dt)
    dt_n = size(dt, 1);
    %%% Modifying the data into symmetric form,
    %%% with diagonal values = 0, all values positive
    %%%-> pairwise approximately Euclidean distance matrix
    for i = 1:dt_n
        for j = 1:dt_n
            dt(i,j) = dt(j,i);
        end
    end

    [Y,e] = cmdscale(dt);

    dims = sum(e > 0.001)
    Y = Y(:, 1:dims);
    e = e(1:dims, 1);

    PVE = e./sum(e);
    cumPVE = cumsum(e)./sum(e);

    %printing the PVE and cumulative PVE
    PVE_results=[PVE cumPVE]
end

