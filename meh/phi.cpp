int phi(int n){
	int ans = n;
	
	for(int i = 0; primes[i] * primes[i] <= n; i++){
		if(n % primes[i] == 0){
			ans /= primes[i];
			ans *= primes[i] - 1;
			
			while(n % primes[i] == 0) n /= primes[i];
		}
	}
	
	if(n > 1){
		ans /= n;
		ans *= n - 1;
	}
	
	return ans;
}