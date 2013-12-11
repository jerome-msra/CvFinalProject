function theta = get_theta(energy)

f2 = get_f2_full(energy);
theta = [energy.f1(:); f2(:)]';

end