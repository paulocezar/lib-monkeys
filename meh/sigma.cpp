//funcao sigma
//Soma dos divisores de n
int sigma(int n){
	int ans = 1;
	
	for(int i = 0; primes[i] * primes[i] <= n; i++){	
		if(n % primes[i] == 0){
			int v = primes[i];
			
			while(n % primes[i] == 0){
				v *= primes[i];
				n /= primes[i]; 
			}
			
			ans *= (v - 1) / (primes[i] - 1);
		}
	}
	
	if(n > 1)
		ans *= n + 1;
		
	return ans;
}