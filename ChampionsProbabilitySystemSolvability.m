clear
syms(sym('a',[1 48]))
eqns = [a1+a2+a3+a4+a5+a6 == 1, a7+a8+a9+a10+a11+a12+a13 == 1,a14+a15+a16+a17+a18 == 1,a19+a20+a21+a22 == 1,a23+a24+a25+a26+a27+a28+a29 == 1,a30+a31+a32+a33+a34+a35 == 1,a36+a37+a38+a39+a40+a41 == 1,a42+a43+a44+a45+a46+a47+a48 == 1,a7+a19+a23+a42 == 1,a1+a14+a20+a28+a30+a36+a43 == 1,a2+a8+a25+a31+a37+a44 == 1,a9+a15+a26+a32+a38+a45 == 1,a3+a10+a16+a33+a39+a46 == 1,a4+a11+a17+a27+a40+a47 == 1,a5+a12+a21+a28+a34+a48 == 1,a6+a13+a18+a22+a29+a35+a41 == 1];
[A,b] = equationsToMatrix(eqns);
M = zeros(48,48);
for i=1:16
    M(i,:) = A(i,:);
end
b = b';
M(:,49) = b(:,1);
U = Max_pivoting(M,48);
for i=1:48
    T(:,i) = U(:,i);
end
disp("The determinant is : ")
disp(det(T))




%now,check that it has infinitely many solutions by seing that there is now
%row of the form 0.....n, where n!=0
for x=1:48
    %we are only interested in the zero rows inside the coefficient matrix 
    %determine if the row is a zero one or not...
    sum = 0; 
    for y=1:48
        sum = abs(U(x,y))+sum;
    end
    if sum == 0
        %this row is an interesting one, so check the independent term on
        %the 49th column
        if U(i,49) ~=0
            disp("No solution!")
            break
        end
    end
end

%function that receives the augmented matrix A|b of a system of linear
%equations and aerforms Maximal aivoting GE to obtain U, uaaer triangular
function U = Max_pivoting( Ab,n)
%inaut aarameters -> Ab is the augmented matrix and n is the size of A
%we assume that the matrix is nonsingular(invertible) so that we wont have
%division by zero in any case 

for i=1:n-1
    %Take the maximum aossible pivot in absolute value
    max_row = i;
    for a=i+1:n
        if(abs(Ab(a,i))>abs(Ab(max_row,i)))
            max_row = a;
        end
    end
    if max_row ~=i
        temp = Ab(i,:);
        Ab(i,:) = Ab(max_row,:);
        Ab(max_row,:) = temp;
    end
    if Ab(i,i) ~=0 %%since the pivot now is the maximal, we wont have to do anything when it is 0 <-> other entries are 0 too
    for j=i+1:n
        m = Ab(j,i)/Ab(i,i);
        Ab(j,:) = Ab(j,:)-(m*Ab(i,:));
    end
    end  
end
U = Ab;
end