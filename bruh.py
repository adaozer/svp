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
                s = scalar_multiply(A_lll[0], v[0])
                for i in range(1,n):
                    s = vector_add(scalar_multiply(A_lll[i], v[i]), s)

            else:
                k -= 1
                for i in range(k+1,n):
                    c[k] = vector_add(scalar_multiply(mu[i][k], v[i]), c[k])
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



def svp_A(A, r):
    A_lll = LLL(A)
    n = len(A_lll)
    mu = [[0 for _ in range(n)] for _ in range(n)]
    B = gram_schmidt(A_lll)
    
    for i in range(n):
        for j in range(i):
            mu[i][j] = inner_product(A_lll[i], B[j]) / inner_product(B[j], B[j])
    
    B_inner = [inner_product(b, b) for b in B]

    p = [0] * (n + 1)
    v = [0] * n
    v[0] = 1
    c = [0] * n
    w = [0] * n
    k = 0
    r_square = r**2
    last_nonzero = 0
    s = None

    while True:
        p[k] = p[k + 1] + (v[k] - c[k])**2 * B_inner[k]
        if p[k] <= r_square:
            if k == 0:
                r_square = p[k]
                s = [0] * len(A_lll[0])
                for i in range(n):
                    s = vector_add(s, scalar_multiply(A_lll[i], v[i]))
                return s  # Exit when the shortest vector is found

            else:
                k -= 1
                c[k] = 0  # Reset c[k] for the current level
                for i in range(k + 1, n):
                    c[k] -= mu[i][k] * v[i]
                v[k] = round(c[k])
                w[k] = 1
        else:
            k += 1
            if k == n:
                if s is not None:
                    return s  # Return the found shortest vector
                k -= 1  # Step back if no vector found

            if k > last_nonzero:
                last_nonzero = k
                v[k] = 1
            else:
                if v[k] > c[k]:
                    v[k] -= w[k]
                else:
                    v[k] += w[k]
                w[k] += 1

B = [[-2, 3, 5, 7, 11, 13, 17], [3, -5, 7, 11, 13, 17, 19], [5, 7, -11, 13, 17, 19, 23], [7, 11, 13, -17, 19, 23, 29], [11, 13, 17, 19, -23, 29, 31], [13, 17, 19, 23, 29, -31, 37], [17, 19, 23, 29, 31, 37, -41]]
R = 50




# Example usage
print("Shortest Vector in B2:", svp_A(B, R))
