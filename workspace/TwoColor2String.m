%return the string of c1 and c2
function s = TwoColor2String (c1,c2,option)

if option ==2
    s1=num2str(c1(1),'%03d');
    
    for i = 2:3
        x=num2str(c1(i),'%03d');
        s1=strcat(s1,x);
    end
    
    s2=num2str(c2(1),'%03d');
    
    for i = 2:3
        x=num2str(c2(i),'%03d');
        s2=strcat(s2,x);
    end
    
    s= strcat(s1,s2);
end
if option == 1
    s1=num2str(c1(1),'%03d');
    s2= num2str(c2(1),'%03d');
    s= strcat(s1,s2);
end

