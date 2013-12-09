%process color image

function [temp,colordistable] = ProcessColor(c1,c2,colordistable,lamda);


 temp =   (lamda^2).*(dot(c1-c2,c2)/(norm(c2))^2)+norm(      c1-(dot(c1,c2).*(c2/(norm(c2))^2) )      );

 
 
colordishash = java.util.Hashtable;
%using the hash table to save the distance of c1 and c2

v = 0.3;
d='hello world';
colordishash.put(d,v);

if colordishash.containsKey(d)
    disp(colordishash.get(d));
end

x=10000;
num2str(x,'%03d')