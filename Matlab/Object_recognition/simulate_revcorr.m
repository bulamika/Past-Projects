
function simulate_revcorr(threshold)
%assumptions: 
%1. do not know how many trials needed
%2. do not know what is the template should be 

%after the simulation, we can be confident to set the # of trials and
%threshold so that we can have a required result of real life experiment
%in terms of real human beings.

%as number of trial increases and averaging them, we can be somewhat
% confident that we get most of the noises (i.e. individual differences)
% out of the result.

if nargin==0
    threshold=0.04; %assumption: 3. we dont know if it is meaningful
end

%%%design noise (gaussian) stimuli
im_n=2000; %number of trials
im_mat=uint8(round(rand(35, 35,im_n)*255));

imtool(imresize(im_mat(:,:,1), 10))


%%%read actual template
targ=imread('red_bowtie.jpg');
targ = im2gray(targ);
%targ = uint8(targ);
targ = imresize(targ,0.01);
targ_vect=double(targ(:));
%size(targ)
imtool(targ)

rho_vect=NaN(im_n, 1);

%%%simulate observer
for im_k=1:im_n
    
    im=im_mat(:,:,im_k);
    im_vect=double(im(:));
    
    rho_vect(im_k)=corr(targ_vect, im_vect);
end

%rho_vect


rho_high=rho_vect >= threshold;
rho_low=rho_vect < threshold;

rho_high_n=sum(double(rho_high))



%%%construct classification image (CI)
im_high=mean(double(im_mat(:,:,rho_high)), 3);
im_low=mean(double(im_mat(:,:,rho_low)), 3);

%imtool(im_high/255)
%imtool(im_low/255)

im_ci=im_high-im_low;

%%% rescale and filter CI for visualization purposes
im_ci_mn=mean(im_ci(:));
im_ci_rescaled=im_ci-im_ci_mn;
im_ci_mx=max(abs(im_ci_rescaled(:)));
im_ci_rescaled=(im_ci_rescaled/im_ci_mx)/2 + 0.5;

imtool(imresize(im_ci_rescaled, 10))

filt = fspecial('gaussian', 19, 3);
im_postfilt = imfilter(im_ci_rescaled, filt, 'same', 'conv');

imtool(imresize(im_postfilt, 10))

