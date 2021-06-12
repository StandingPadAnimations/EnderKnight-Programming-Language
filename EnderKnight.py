from EKLexer import EKLexer
from EKEvaluator import EKEvaluator
import sys
import time 

def main():
    filename = sys.argv[1]
    
    if len(sys.argv) == 3:
        error_handeling = sys.argv[2]
    else:
        error_handeling = None 
        
    file = open(filename, 'r')
    lexer = EKLexer(file)
    
    lexer.tokenizer()
    #print("TOKENS:")
    #print(lexer.tokens, "\n")
    #print(lexer.variables)
    evaluator = EKEvaluator(lexer.tokens, lexer.variables)
    
    if len(lexer.errors) == 0 or error_handeling == '--run-with-errors':
        if error_handeling == '--run-with-errors':
            print("--run-with-errors has been specified. All Errors will be posted now if any and execution will be delayed by 2 seconds:")
            if len(lexer.errors) > 0:
                for error in lexer.errors:
                    print(error)
            time.sleep(2)
            print("\n")
            print("EnderKnight Python Port Beta 4:")
            evaluator.execute()
            
        else:
            print("EnderKnight Python Port Beta 4:")
            evaluator.execute()
        
    elif error_handeling == None and len(lexer.errors) > 0:
        print(f"EnderKnight Traceback: {len(lexer.errors)} errors; could not evaluate due to error count higher then 0. Errors are:")
        for error in lexer.errors:
            print(error)




if __name__ == "__main__":
    main()