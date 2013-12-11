function R = color_transform(I,A)
%
%		color_transform(I,A) -- linear transform of the colors in image I
%
%		Input: I -- image; A -- 3 x 4 matrix.
%
%		Output: R -- image with adjusted colors.
%
%
cc = msize(I,3);

if(size(A)~=[cc cc+1])
	error(['A must be ' num2str(cc) 'x' num2str(cc+1) '. In R = color_transform(I,A)']);
end

I = im2double(I);
    d  = size(I,3);
    R = zeros(size(I));
    for i=1:d
        R(:,:,i) = A(i,d+1);
        for j=1:d 
            R(:,:,i) = R(:,:,i) + I(:,:,j)*A(i,j);
        end
    end
end