function IT = inverse(T)
%
%		IT = inverse(T) -- inverse of T
%

IT = geom_transform(fliptform(T.form));

end