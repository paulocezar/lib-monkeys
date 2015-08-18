// if in tree exists more than one index with a same
// cumulative frequency, this procedure will return 
// some of them (we do not know which one)

// bitMask - initialy, it is the greatest bit of MaxVal
// bitMask store interval which should be searched
int find(int cumFre) {
	int idx = 0; // this var is result of function
	
	while ((bitMask != 0) && (idx < MaxVal)) { // nobody likes overflow :)
		int tIdx = idx + bitMask; // we make midpoint of interval
		if (cumFre == tree[tIdx]) // if it is equal, we just return idx
			return tIdx;
		else if (cumFre > tree[tIdx]){ 
		        // if tree frequency "can fit" into cumFre,
		        // then include it
			idx = tIdx; // update index 
			cumFre -= tree[tIdx]; // set frequency for next loop 
		}
		bitMask >>= 1; // half current interval
	}
	if (cumFre != 0) // maybe given cumulative frequency doesn't exist
		return -1;
	else
		return idx;
}

// if in tree exists more than one index with a same
// cumulative frequency, this procedure will return 
// the greatest one
int findG(int cumFre){
	int idx = 0;
	
	while ((bitMask != 0) && (idx < MaxVal)){
		int tIdx = idx + bitMask;
		if (cumFre >= tree[tIdx]){ 
		        // if current cumulative frequency is equal to cumFre, 
		        // we are still looking for higher index (if exists)
			idx = tIdx;
			cumFre -= tree[tIdx];
		}
		bitMask >>= 1;
	}
	if (cumFre != 0)
		return -1;
	else
		return idx;
}