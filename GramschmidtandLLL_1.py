def dot_product(vec1, vec2):
    return sum(a * b for a, b in zip(vec1, vec2))


def subtract_vector(vec1, vec2):
    return [a - b for a, b in zip(vec1, vec2)]

def gram_schmidt(B):
    n=len(B)
    U=[B[0][:]] #u1=v1
    for i in range(1,n):
        Vi=B[i][:]
        for j in range(i):
            proju = dot_product(B[i], U[j]) / dot_product(U[j], U[j]) #this is the GS coeeficients but is it more effiecient to pass this here now or is it better off me calculating every time i reinistalise wiat 
            Vi = subtract_vector(Vi, [proju * x for x in U[j]])
        
        U.append(Vi)
    return U

                                
def LLL_Reduction(Basis,delta=0.75): ####maybe my indexing 1 to great cause of psuedocode starting at 1 and python starting at 0 please check this
    n=len(Basis)
    orthobasis=gram_schmidt(Basis) #this defo works
    mu = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        mu[i][i] = 1
        for j in range(i):
            mu[i][j] = dot_product(Basis[i], orthobasis[j]) / dot_product(orthobasis[j], orthobasis[j])
    
    k=1
    while k<=n-1:
        for j in range(k)[::-1]:    
            #μk,j
            if abs(mu[k][j]) > 1/2:
                mukj=round(mu[k][j])
                Basis[k] = subtract_vector(Basis[k], [(mukj)* x for x in Basis[j]])#⌊μk,j⌉bj# 
                for L in range(j+1):
                    mu[k][L] -=mukj*(mu[j][L])
                
                #orthobasis = gram_schmidt(Basis) #niave approuch theoretically quicker just to change what changes in the orthobasis B but for the low dimensions not worth it 
                    
        if dot_product(orthobasis[k],orthobasis[k]) > (delta - (mu[k][k-1])**2)*dot_product(orthobasis[k-1],orthobasis[k-1]):
            k=k+1

        else:
            temp=Basis[k]
            Basis[k]=Basis[k-1]
            Basis[k-1]=temp
            orthobasis=gram_schmidt(Basis)
            mu = [[0 for _ in range(n)] for _ in range(n)]
            for i in range(n):
                mu[i][i] = 1
                for j in range(i):
                    mu[i][j] = dot_product(Basis[i], orthobasis[j]) / dot_product(orthobasis[j], orthobasis[j])
            k = max(k - 1, 1)

    return Basis #reduced by LLL basis this should speed up enumeration



def Schnorr_Euchner_Enumeration(Basis, n, R):
    orthobasis=gram_schmidt(Basis)
    B_star_squared=[]
    mu = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        mu[i][i] = 1
        for j in range(i):
            mu[i][j] = dot_product(Basis[i], orthobasis[j]) / dot_product(orthobasis[j], orthobasis[j])
    

    for i in range(n):
        B_star_squared.append(dot_product(orthobasis[i], orthobasis[i]))

    
    sigma= [[0 for _ in range(n)] for _ in range(n+1)]
    r= [0] * (n+1)
    for i in range(n+1):
        r[i]=i
    
    rho = [0] * (n+1)
    v = [0] * (n+1)
    v[0]=1
    c = [0] * n
    w = [0] * n
    k=1
    last_nonzero=1
    loops = 0
    while True:
        loops = loops+1
        rho[k-1] = rho[k] + (((v[k-1] - c[k-1])**2)*B_star_squared[k-1])
        if rho[k-1] < R:
            if k==1:
                print("Solution Found")
                vec=Matrix_X_Number(Basis[0],v[0])
                #list issues only an issue in python cause its a list but itll be as an array just like vec=Basis[0]*v[0] 
                for i in range(1,n):
                    matrixtoadd=Matrix_X_Number(Basis[i],v[i])#once again it should just be vec+=v[i]*B[i]
                    new=[vec,matrixtoadd]
                    vec=[sum(x) for x in zip(*new)]
                R=dot_product(vec, vec)
                print("Norm=", R**0.5, ", Vector=", vec)
            else:
                k=k-1
                #sigma=0
                ####THIS MIGHT BE THE SHIT FUCKING MY CODE I CANT TELL TBH
                
                r[k-1] = max(r[k-1], r[k])
                print('r',r[k-1])
                print(k)
                for i in range(k+1, r[k]+1)[::-1]:
                    print(i)
                    sigma[i-1][k-1]=sigma[i][k-1]+(mu[i-1][k-1]*v[i-1])
                c[k-1]= -sigma[k][k-1]
                ####
                v[k-1]=round(c[k-1])
                w[k-1]=1
        else:
            k=k+1
            if k==n+1:
                print("no solution")
                return False
            r[k-1] = k
            if k >= last_nonzero:
                last_nonzero=k
                v[k-1] = v[k-1] + 1
            else:
                if v[k-1]>c[k-1]:
                    v[k-1]= v[k-1] - w[k-1]
                else:
                    v[k-1] = v[k-1] + w[k-1]
                w[k-1]=w[k-1]+1  
        if loops == 3:
            return 0

            
                

            



        
def Matrix_X_Number(matrix,number):
    x=matrix.copy()
    for i in range(len(x)):
        x[i]=x[i]*number
    return x






B4 = [[1, 2, 3, 4],
      [2, 3, 4, 5],
      [3, 4, 5, 6],
      [4, 5, 6, 7]]
Basis=LLL_Reduction(B4)
#print('Basis',Basis)
R=dot_product(B4[0], B4[0])
n=len(B4)
print("Norm=", R**0.5, ", Vector=", B4[0])
v=Schnorr_Euchner_Enumeration(B4, n, R)                              
print("end")



    