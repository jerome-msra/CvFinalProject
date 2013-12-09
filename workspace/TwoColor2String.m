%return the string of c1 and c2
function s = StringCC (c1,c2);

c1=[1 1 1];
c2=[1 1 1];
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
