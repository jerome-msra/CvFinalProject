%the color distance table the first parameter is the row
%the second parameter is col
%the order is RGB
%lamda  = 0.1
%function dis = color_dis(option);

option = 2;
warning off
% ȡģ��norm��x��,norm(y)
% �нǣ�acos(dot(x,y)/norm(x)/norm(y))
lamda = 0.1;
t1=clock;
if option == 1
    % gray graph
    dis = zeros(256,256);
    for i = 1:256
        for j = 1:256
            c1 = (i-1)/255;
            c2 = (j-1)/255;
            dis(i,j) = (lamda^2)*(dot(c1-c2,c2)/(norm(c2))^2) + (c1-dot(c1,c2)*c2/(norm(c2))^2)^2;
        end
    end
else if option ==2
        % color graph
        limit = 256;
        for ai =1: limit
            ai
            for aj =1: limit
                for ak=1: limit
                    c1=[(ai-1)/255 (aj-1)/255 (ak-1)/255];
                    for bi =1: limit
                        for bj=1: limit
                            for bk =1: limit
                                c2 = [(bi-1)/255 (bj-1)/255 (bk-1)/255];
                                dis(ai,aj,ak,bi,bj,bk) =  (lamda^2).*(dot(c1-c2,c2)/(norm(c2))^2)+norm(      c1-(dot(c1,c2).*(c2/(norm(c2))^2) )      );
                            end
                        end
                    end
                end
            end
        end
    end
end
t2= clock;

etime(t2,t1)









