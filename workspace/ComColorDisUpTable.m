%string Color
function dis = ComColorDisUpTable(c1,c2,ColorDisHash,lamda);
tempc1= c1;
tempc2= c2;

    
    
    
    



    distance =   (lamda^2).*(dot(c1-c2,c2)/(norm(c2))^2)+norm(      c1-(dot(c1,c2).*(c2/(norm(c2))^2) )      );
    ColorDisHash.put(s,distance);