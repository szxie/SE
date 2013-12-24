function [ output_args ] = CircleT(  )
    imID=3;
    img = imread(['../data/r','0'+imID,'s2.jpg']);
    imgs = imread(['../data/t','0'+imID,'.jpg']);
    close all;
    figure, imshow(imgs);
    
    C = [1,1];
    T = [C(1),C(2)];
    i = 0;
    siz = size(img);
    rmin=30;
    rmax=50;
    Max=10;
    while 1
        Counter=0;
        dist = zeros(siz(1),siz(2));
    for m = 1:siz(1)
        for n = 1:siz(2)
            if img(m,n)>0
                dist(m,n) = sqrt((C(1)-m)^2+(C(2)-n)^2);
                if dist(m,n)>rmin && dist(m,n)<rmax
                    Counter = Counter+1;
                end
            end
        end
    end
    if Counter > Max
        Max = Counter;
        T = C;
        %viscircles(T, [0.5], 'EdgeColor', 'r');        
        hold all;
        plot(T(1),T(2), '.','markersize', 20);
    end
        C(1) = C(1)+1;
        if (C(1)>siz(1))
            C(2) = C(2)+1;
            C(1) = 1;
            if C(2)>siz(2)
                T;
                break;
            else
                continue;
            end
        else
            continue;
        end
    
    end

    viscircles(T, [rmin], 'EdgeColor', 'b');
end