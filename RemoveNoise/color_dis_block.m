%color_dis_block
function dis  = color_dis_block(template,target,indexs,indexts,blocksize,option);
%block size are not appropriate

lamda = 0.1;

if option ==1
    templatesize = size(template);
    targetsize = size(target);
    
    indexs = indexs+blocksize;
    indexts = indexts + blocksize;
    
    
    s_template = -indexs + templatesize;
    s_target= -indexts + targetsize;
    
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
                c1 =( template(indexs(1)+i,indexs(2)+j)-1)/255;
                c2=( target(indexts(1)+i,indexts(2)+j)-1)/255;
                
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
                
                c1 =( template(indexs(1)+i,indexs(2)+j)-1)/255;
                c2=( target(indexts(1)+i,indexts(2)+j)-1)/255;
                
                temp =   (lamda^2)*(dot(c1-c2,c2)/(norm(c2))^2) + (c1-dot(c1,c2)*c2/(norm(c2))^2)^2;
                temps = temps+temp;
                
            end
        end
        
        temps = temps /(blocksize*blocksize);
        
        
        
    end
    
    
end

if option ==2
    
    templatesize = size(template);
    targetsize = size(target);
    
    indexs = indexs+blocksize;
    indexts = indexts + blocksize;
    
    
    s_template = -indexs + templatesize;
    s_target= -indexts + targetsize;
    
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
                c1 =( template(indexs(1)+i,indexs(2)+j,:)-1)/255;
                c2=( target(indexts(1)+i,indexts(2)+j,:)-1)/255;
                
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
                
                c1 =( template(indexs(1)+i,indexs(2)+j,:)-1)/255;
                c2=( target(indexts(1)+i,indexts(2)+j,:)-1)/255;
                
                temp =   (lamda^2)*(dot(c1-c2,c2)/(norm(c2))^2) + (c1-dot(c1,c2)*c2/(norm(c2))^2)^2;
                temps = temps+temp;
                
            end
        end
        
        temps = temps /(blocksize*blocksize);

    end
    
    
    
end


dis = temps;





