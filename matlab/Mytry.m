function [ output_args ] = Mytry(  )
    %TRY Summary of this function goes here
    %   Detailed explanation goes here
    i =3;
    close all;
    img = imread(['../data/t','0'+i,'.jpg']);
    img_gray = rgb2gray(img);
    img_edge = edge(img_gray, 'canny');
    figure, imshow(img_edge);
    maxl=75;
    %75 for 1
    minl=0;
    %figure,imhist(img_gray);
    figure,imshow(img);
    s1 = size(img_gray);
    for m = 1:s1(1)
        for n = 1:s1(2)
            if img_gray(m,n) < minl || img_gray(m,n)>maxl
                img_gray(m,n) = 0;
            else
                img_gray(m,n) = 255;
            end
        end    
    end
    %[centers,radii] = imfindcircles(img_gray, [5,100], 'ObjectPolarity', 'dark');
    figure,imshow(img_gray);
    imwrite(img_gray, ['../data/r','0'+i,'s1.jpg']);
    %im2=imfill(img_gray,'holes');
    im2 = img_gray;
    im3=bwperim(im2);
    figure,imshow(im2);
    figure,imshow(im3);
    imwrite(im3, ['../data/r','0'+i,'s2.jpg']);
    %viscircles(centers(1:1,:), radii(1:1),'EdgeColor', 'b');
    %[max1,id1] = max(a);
    %a(id1) = -1;
    %[max2,id2] = max(a);
    %id1;
    %id2;
    
end
