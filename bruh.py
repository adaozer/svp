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

def norm(u):
    counter_2 = 0
    for i in u:
        counter_2 += i**2
    return counter_2**(1/2)

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
    #for i in range(len(orthogonal_basis)):
        #orthogonal_basis[i] = scalar_multiply(orthogonal_basis[i], 1/norm(orthogonal_basis[i]))
    return orthogonal_basis

def LLL(A, S=3/4):
    B = gram_schmidt(A)
    n = len(B)

    mu = [[0 for i in range(n)] for i in range(n)]

    for i in range(n):
        for j in range(len(mu[i])-1):
            mu[i][j] = inner_product(A[i], B[j])/inner_product(B[j], B[j])

    k = 1
    while k < n:
        for j in range(k-1, -1, -1):
            if abs(mu[k][j]) > 1/2:
                tempp = scalar_multiply(A[j], round(mu[k][j]))
                A[k] = vector_subtraction(A[k], tempp)
                B = gram_schmidt(A)
                for i in range(k+1):
                    for p in range(len(mu[i])-1):
                        mu[i][p] = inner_product(A[i], B[p])/inner_product(B[p], B[p])
        if inner_product(B[k], B[k]) > (S-((mu[k][k-1]))**2)* inner_product(B[k-1], B[k-1]):
            k += 1
        else:
            temp = A[k]
            A[k] = A[k-1]
            A[k-1] = temp
            B = gram_schmidt(A)
            for i in range(k+1):
                for g in range(len(mu[i])-1):
                    mu[i][g] = inner_product(A[i], B[g])/inner_product(B[g], B[g])
            k = max(k-1, 1)

    return A

def svp(A, r):
    A_lll = LLL(A)
    n = len(A_lll)
    mu = [[0 for i in range(n)] for i in range(n)]
    B = gram_schmidt(A_lll)
    for i in range(n):
        for j in range(len(mu[i])-1):
            mu[i][j] = inner_product(A_lll[i], B[j])/inner_product(B[j], B[j])
    
    B_inner = []
    for i in B:
        B_inner.append(inner_product(i,i))
  
    p = [0] * (n+1)
    v = [0] * n
    c = [0] * n
    w = [0] * n
    v[0] = 1
    k = 0
    r_square = r**2
    last_nonzero = 0

    while True:
        p[k] = p[k+1] + (v[k] - c[k])**2 * B_inner[k]
        if p[k] <= r_square:
            if k == 0:
                r_square = p[k]
                s = [sum(v[i-1] * A_lll[i - 1][j] for i in range(1, n + 1)) for j in range(len(A_lll[0]))]
            else:
                k -= 1
                c[k] = -sum(mu[i][k] * v[i] for i in range(k + 1, n))
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


print(svp([[3,4], [-4,3]], 6))
