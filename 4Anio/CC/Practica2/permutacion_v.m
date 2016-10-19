function permuta = permutacion_v(p)

d = length(p);
A = [1:d];
B = sort(p);
if A == B
    permuta = 1;
else
    permuta = 0;
end