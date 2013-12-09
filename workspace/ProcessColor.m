%process color image
colordishash = java.util.Hashtable;
%using the hash table to save the distance of c1 and c2
c1 = 0.1;
c2 = 0.2;
v = 0.3;
c={c1,c2}
colordishash.put(c ,v);

if colordishash.containsKey(c)
    disp(colordishash.get(c));
end


