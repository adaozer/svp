from math import sqrt

def inner_product(u, v):
    counter = 0
    for i in range(len(u)):
        counter += u[i]*v[i]
    return counter

def scalar_multiply(u, scalar):
    result = []
    for i in u:
        result.append(i*scalar)
    return result

def vector_subtraction(u, v):
    result_2 = []
    for i in range(len(u)): 
        result_2.append(u[i]-v[i])
    return result_2


def normalize(vector):
    norm = (inner_product(vector, vector))**0.5
    return scalar_multiply(vector, 1/norm)

def gram_schmidt(A):
    orthogonal_basis = [A[0]]
    for i in range(1,len(A)):
        counter = 0
        hats = []
        while counter < i:
            hat_top = inner_product(A[i], orthogonal_basis[counter])
            hat_bottom = inner_product(orthogonal_basis[counter], orthogonal_basis[counter])
            hat_final = scalar_multiply(orthogonal_basis[counter], hat_top/hat_bottom)
            hats.append(hat_final)
            counter += 1
        result = A[i]
        for hat in hats:
            result = vector_subtraction(result, hat)
        orthogonal_basis.append(result)
    
    return orthogonal_basis

def vector_add(u, v):
    result = []
    for i in range(len(u)):
        result.append(u[i]+v[i])
    return result

def LLL(Basis, S=3/4):
    n = len(Basis)
    orthobasis = gram_schmidt(Basis)


    mu = [[0 for _ in range(n)] for _ in range(n)]

    for i in range(n):
        mu[i][i] = 1
        for j in range(i):
            mu[i][j] = inner_product(Basis[i], orthobasis[j])/inner_product(orthobasis[j], orthobasis[j])

    k = 1
    while k < n:
        for j in range(k-1, -1, -1):
            if abs(mu[k][j]) > 1/2:
                tempp = scalar_multiply(Basis[j], round(mu[k][j]))
                Basis[k] = vector_subtraction(Basis[k], tempp)
                orthobasis = gram_schmidt(Basis)
                for i in range(n):
                    for p in range(len(mu[i])-1):
                        mu[i][p] = inner_product(Basis[i], orthobasis[p])/inner_product(orthobasis[p], orthobasis[p])
        if inner_product(orthobasis[k], orthobasis[k]) > (S-((mu[k][k-1]))**2)* inner_product(orthobasis[k-1], orthobasis[k-1]):
            k += 1
        else:
            temp = Basis[k]
            Basis[k] = Basis[k-1]
            Basis[k-1] = temp
            orthobasis = gram_schmidt(Basis)
            for i in range(n):
                    for z in range(len(mu[i])-1):
                        mu[i][z] = inner_product(Basis[i], orthobasis[z])/inner_product(orthobasis[z], orthobasis[z])
            k = max(k-1, 1)

    return Basis


def schnorr_euchner(A, R):
    B = gram_schmidt(A)
    n = len(A)
    B_inner = []
    for i in range(len(B)):
        B_inner.append(inner_product(B[i], B[i]))

    mu = [[0 for i in range(n)] for i in range(n)]
    for i in range(len(mu)):
        for j in range(i):
            mu[i][j] = inner_product(A[i], B[j])/inner_product(B[j], B[j])

    p = [0] * (n+1)
    v = [0] * n
    v[0] = 1
    c = [0] * n
    w = [0] * n
    k = 0
    last_nonzero = 0
    R_squared = R**2
    s = [A[0]]

    while True:
        p[k] = p[k+1] + (v[k] + c[k])**2 * B_inner[k]
        
        if p[k] < R_squared: # Bu eşittirin amına koydum
            if k == 0:
                R_squared = p[k]
                s = [0 for _ in range(len(A[0]))]
                for i in range(n):
                    s = vector_add(scalar_multiply(A[i], v[i]), s)
                                
            else:
                k -= 1
                c[k] = 0
                for i in range(k+1, n):
                    c[k] += mu[i][k]*v[i]
                c[k] *= -1
                v[k] = round(c[k])
                w[k] = 1
        else:
            k += 1
            if k == n:
                return s
            if k >= last_nonzero:
                last_nonzero = k
                v[k] += 1
            else:
                if v[k] > c[k]:
                    v[k] -= w[k]
                else:
                    v[k] += w[k]
                w[k] += 1

def find_length(v):
    result = 0
    for i in range(len(v)):
        result += v[i]**2
    
    return sqrt(result)

b = [[44.1, 50.99] ,[220.0, 44.0]]

lll = LLL(b)
r = sqrt(inner_product(b[0],b[0]))


l = schnorr_euchner(lll, r)
print(find_length(l))
