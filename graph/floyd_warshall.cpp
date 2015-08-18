/* 
	init: p[i][j] = i;
	if (i,k)+(k,j) < (i,j)
	 p[i][j] = p[k][j]
*/
         
         
void show( int from, int to ){
	if( from != to ){
		show( from, p[from][to] );
		cout << " ";
	}
	cout << to;
}
