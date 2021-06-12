import re


class EKEvaluator:
    
    def __init__(self, ek_tokens, ek_variables): 
        self.tokens = ek_tokens
        self.variables = ek_variables
        self.goto_has_been_called = False

    def execute(self):
        for token in self.tokens:
            if token['id'] == 'echo':
                self.echo(token['value'])
                #print(f'variables are {self.variables}')
                
            if token['id'] == 'stop':
                self.stop()
                
            elif token['id'] == 'math':
                self.math(token['value'])
                
            elif token['id'] == 'goto':
                self.goto(token['value'])
                
            elif token['id'] == 'edef':
                self.stop()
                
            elif token['id'] == '/*':
                pass 
            
            elif token['id'] == 'if':
                self.if_process(token['value'])

    def echo(self, v):
        v = v.replace('echo', '')
        if '''"''' not in v:
            v = v.replace(' ', '', 1)
            if v in self.variables:
                v = self.variables[v].replace('"', '')
                print(v)
        else:
            v = v.replace('"', '').replace(' ', "", 1)
            print(v)
        
    def stop(self):
        if self.goto_has_been_called == False:
            quit()
        
    def goto(self, v):
        self.goto_has_been_called = True 
        v = v.replace('goto', 'edef')
        for edef in self.tokens:
            if edef['id'] == 'edef':
                edef_definition = edef['value']
                edef_definition = edef_definition.replace(':', '')
                if edef_definition == v:
                    edef_statement = self.tokens.index(edef)
                    v = v.replace('edef', '').replace(' ', '', 1) 
                    for edef in self.tokens:
                        if edef['id'] == 'end_edef':
                            edef_value = edef['value'].replace('end_edef', '').replace(' ', '')
                            if edef_value == v:
                                end_edef_statement = self.tokens.index(edef)
                                for token in self.tokens[edef_statement:end_edef_statement]:
                                    if token['id'] == 'echo':
                                        self.echo(token['value'])
                                        #print(f'variables are {self.variables}')
                                        
                                    if token['id'] == 'math':
                                        self.math(token['value'])
                                        
                                    if token['id'] == 'goto':
                                        self.goto(token['value'])
                                        #pass 
                                        
                                    self.goto_has_been_called = False
                
    def math(self, v):
        v = v.replace('math', '').replace(' ', '', 1)
        print(eval(v))
        
        
    def if_process(self, v):
        if_name = re.findall('//(.*?)//', v, re.DOTALL)
        for end_if_state in self.tokens:
            if end_if_state['id'] == 'end_if_state':
                print(end_if_state['id'])
                
        
    def set_variable(self, v):
        variable_meaning = v.split('=') 
        self.variables.update({variable_meaning[0] : variable_meaning[1]})
        
        