function mesh_plot(r1,r2)
	plot([reshape(r1(:,1:end-1),1,[]); reshape(r1(:,2:end),1,[])],[reshape(r2(:,1:end-1),1,[]); reshape(r2(:,2:end),1,[])],'-b');
	hold on;
	plot([reshape(r1(1:end-1,:),1,[]); reshape(r1(2:end,:),1,[])],[reshape(r2(1:end-1,:),1,[]); reshape(r2(2:end,:),1,[])],'-b');
	%plot(r1(:),r2(:),'.w');
end