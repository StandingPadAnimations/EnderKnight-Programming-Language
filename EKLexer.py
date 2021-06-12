class EKLexer:
    
    def __init__(self, data):
        self.data = data 
        self.tokens = []
        self.keywords = [
            'echo',
            'goto',
            'stop',
            'math',
            'var',
            'edef',
            'end_edef',
            '/*',
            'if',
            'endif'
        ]
        self.variables = {}
        self.errors = [] 
        

    def tokenizer(self):
        for loc in self.data:
            loc_split = loc.split()
            #print(loc_split)
            
            if len(loc_split) > 0:
                if loc_split[0] in self.keywords:
                    if loc_split[0] == 'var':
                        text = ' '.join(loc_split)
                            
                        if '=' not in text:
                            self.errors.append(f"Invalid Syntax: {text} missing '='")
                            
                            
                            
                        else:
                            variable = text.replace('var', '').split('=')
                            if variable[0].replace(' ', "") in self.keywords:
                                self.errors.append(f'Invalid Variable Name: {variable[0]} is also a keyword')
                                
                                
                            elif variable[0].replace(' ', "") in self.variables:
                                self.errors.append(f'Invalid Variable Name: {variable[0]} has already been set')
                                

                            else:
                                self.tokens.append({"id" : "variable", "value" : f'{text}'})
                                self.variables.update({variable[0].replace(' ', "") : variable[1].replace(' ', "", 1)})
                                #print(self.variables)
                            
                        #print(self.tokens)
                            
                    elif loc_split[0] == 'echo':
                        text = ' '.join(loc_split)
                            
                        self.tokens.append({"id" : "echo", "value" : text})
                            
                        #print(self.tokens)
                            
                    elif loc_split[0] == 'edef':
                        text = ' '.join(loc_split)
                        self.tokens.append({"id" : "edef", "value" : text})
                            
                        #print(self.tokens)
                            
                    elif loc_split[0] == 'math':
                        text = ' '.join(loc_split)
                        self.tokens.append({"id" : "math", "value" : text})
                            
                        #print(self.tokens)
                            
                    elif loc_split[0] == 'stop':
                        self.tokens.append({"id" : "stop", "value" : loc})
                            
                        #print(self.tokens)
                            
                    elif loc_split[0] == 'goto':
                        text = ' '.join(loc_split)
                        self.tokens.append({"id" : "goto", "value" : text})
                            
                        #print(self.tokens)
                            
                    elif loc_split[0] == 'end_edef':
                        text = ' '.join(loc_split)
                        self.tokens.append({"id" : "end_edef", "value" : text})
                            
                        #print(self.tokens)
                            
                    elif loc_split[0] == '/*':
                            text = ' '.join(loc_split)
                            self.tokens.append({"id" : "/*", "value" : text})
                            
                            
                    elif loc_split[0] == 'if':
                        text = ' '.join(loc_split)
                        if '//' not in text:
                            self.errors.append(f"Invalid Syntax: {text} missing '// //' with if statement name")
                            
                        
                        else:
                            self.tokens.append({"id" : "if", "value" : text})
                        
                    elif loc_split[0] == 'end_if_state':
                        text = ' '.join(loc_split)
                        self.tokens.append({"id" : "end_if_state", "value" : text})
                        