//find the first and follow of a production
//First and Follow are used in parsing to construct predictive parsers, especially LL(1) parsers.
/*First(X): The set of terminals that appear at the beginning of some string derived from X.
    For a terminal, it is the terminal itself.
    For a non-terminal, it may contain terminals and ε (empty string).
Follow(X): The set of terminals that can appear immediately to the right of X in some sentential form.
*/

void first(char nonterm){
    int index = 0;
    char curr_firsts[50];
    for(int i = 0; i<n;i++){
        if(prods[i][0] == nonterm){
            int curr_prod_index = 0;
            int flag = 0;
            while(prods[i][curr_prod_index] != '\0' && flag==0){
                flag = 1;
                if (isTerminal(prods[i][curr_prod_index])){
                    curr_firsts[index] = prods[i][2];
                    index++;
                    break;
                }
                if (!is_first_done[prods[i][curr_prod_index] -65])first(prods[i][curr_prod_index]);
                int in = 0;
                while(firsts[prods[i][curr_prod_index]-65][in] != '\0'){
                    curr_firsts[index] = firsts[prods[i][curr_prod_index]][in];
                    if (firsts[prods[i][curr_prod_index]-65][in] == 'e'){
                        curr_prod_index++;
                        flag = 0;
                    }
                    index++;
                    in++;
                }
            }
        }
    }
    curr_firsts[index] = '\0';
    index++;
    strcpy(firsts[nonterm-65], curr_firsts);
    is_first_done[nonterm-65] = 1;
}