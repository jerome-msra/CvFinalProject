%color_dis_block
function dis  = color_dis_block(template,target,indexs,indexts,blocksize,ColorDisHash,option);
%block size are not appropriate
% option = 1 for grey graph
% option = 2 for colour graph
lamda = 0.1;

% template = double(imread('template.png'));
% target = double (imread('target1.png'));
%
% indexs = [100 100];
% indexts = [100 100];
% blocksize = 4;
% option = 2;


% template = imread('template.png');
% template = rgb2gray(template);
% figure,imshow (template);
% target = imread('target1.png');
% target = rgb2gray(target);
%
% figure,imshow(target);
%
%
% indexs = [100 100];
% indexts = [100 100];
%
% blocksize = 4;
% option = 1;


if option ==1
    templatesize = size(template);
    targetsize = size(target);
    
    
    if indexs(1)>templatesize(1) || indexs(2)>templatesize(2)
        disp('extend the bounday');
    else
        
        
        
        t_indexs = indexs+blocksize;
        t_indexts = indexts + blocksize;
        
        
        s_template = -t_indexs + templatesize;
        s_target= -t_indexts + targetsize;
        
        if s_template(1)<0 || s_template(2)<0 || s_target(1)<0 || s_target(2)<0
            %different blocksize
            %for the rows
            if s_template(1)<0
                r_blocksize = blocksize - abs(s_template(1));
            end
            
            if s_target(1)<0
                r_blocksize = min(blocksize - abs(s_target(1)),r_blocksize);
            end
            
            if s_template(2)<0
                c_blocksize = blocksize - abs(s_template(2));
            end
            
            if s_target(2)<0
                c_blocksize = min(blocksize - abs(s_target(2)),c_blocksize);
            end
            
            temps = 0;
            
            for i = 0: r_blocksize-1
                for j = 0: c_blocksize-1
                    c1 =double( template(indexs(1)+i,indexs(2)+j)-1)/255.0;
                    c2=double( target(indexts(1)+i,indexts(2)+j)-1)/255.0;
                    c1= double(c1);
                    c2 = double (c2);
                    temp =   (lamda^2)*(dot(c1-c2,c2)/(norm(c2))^2) + (c1-dot(c1,c2)*c2/(norm(c2))^2)^2;
                    temps = temps+temp;
                end
            end
            
            
            temps = temps/(r_blocksize*c_blocksize);
            
        else
            %compute two different blocks' distance
            temps = 0;
            for i = 0:(blocksize-1)
                for j = 0:(blocksize-1)
                    
                    c1 =double( template(indexs(1)+i,indexs(2)+j)-1)/255.0;
                    c2=double( target(indexts(1)+i,indexts(2)+j)-1)/255.0;
                    c1= double(c1);
                    c2 = double (c2);
                    temp =   (lamda^2)*(dot(c1-c2,c2)/(norm(c2))^2) + (c1-dot(c1,c2)*c2/(norm(c2))^2)^2;
                    temps = temps+temp;
                    
                end
            end
            
            temps = temps /(blocksize*blocksize);
            
        end
        
    end
    
end

if option ==2
    
    templatesize = size(template);
    targetsize = size(target);
    
    templatesize = templatesize(:,1:2);
    targetsize = targetsize(:,1:2);
    
    
    if indexs(1)>templatesize(1) || indexs(2)>templatesize(2)
        disp('extend the bounday');
    else
        
        
        t_indexs = indexs+blocksize;
        t_indexts = indexts + blocksize;
        
        
        s_template = -t_indexs + templatesize;
        s_target= -t_indexts + targetsize;
        
        if s_template(1)<0 || s_template(2)<0 || s_target(1)<0 || s_target(2)<0
            %different blocksize
            %for the rows
            if s_template(1)<0
                r_blocksize = blocksize - abs(s_template(1));
            end
            
            if s_target(1)<0
                r_blocksize = min(blocksize - abs(s_target(1)),r_blocksize);
            end
            
            if s_template(2)<0
                c_blocksize = blocksize - abs(s_template(2));
            end
            
            if s_target(2)<0
                c_blocksize = min(blocksize - abs(s_target(2)),c_blocksize);
            end
            
            temps = 0;
            
            for i = 0: r_blocksize-1
                for j = 0: c_blocksize-1
                    
                    c1 =double( template(indexs(1)+i,indexs(2)+j,:)-1)/255.0;
                    c1 = [c1(1,1,1)  c1(1,1,2) c1(1,1,3)];
                    c2=double( target(indexts(1)+i,indexts(2)+j,:)-1)/255.0;
                    c2= [c2(1,1,1) c2(1,1,2) c2(1,1,3)];
                    temp =   (lamda^2).*(dot(c1-c2,c2)/(norm(c2))^2)+norm(      c1-(dot(c1,c2).*(c2/(norm(c2))^2) )      );
                    temps = temps+temp;
                    
                end
            end
            
            temps = temps/(r_blocksize*c_blocksize);
            
        else
            %compute two different blocks' distance
            temps = 0;
            limit = blocksize - 1;
            
            for i = 0:limit
                for j = 0:limit
                    
                    c1 =double( template(indexs(1)+i,indexs(2)+j,:)-1)/255.0;
                    c1 = [c1(1,1,1)  c1(1,1,2) c1(1,1,3)];
                    c2=double( target(indexts(1)+i,indexts(2)+j,:)-1)/255.0;
                    c2= [c2(1,1,1) c2(1,1,2) c2(1,1,3)];
                    temp =   (lamda^2).*(dot(c1-c2,c2)/(norm(c2))^2)+norm(      c1-(dot(c1,c2).*(c2/(norm(c2))^2) )      );
                    temps = temps+temp;
                    
                end
            end
            
            temps = temps /(blocksize*blocksize);
            
        end
        
    end
    
end


dis = temps;





