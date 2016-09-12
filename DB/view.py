class View:
    @staticmethod
    def data_base_menu():
        print 'Data base menu\n'
        print 'Choose one of the following items\n'
        print '1) Cinemas menu'
        print '2) Sessions menu'
        print '3) Exit'

    @staticmethod
    def display(lst):
        for element in lst:
            print '\n'.join(map(lambda key: key + ' : ' + element[key]), element.keys())
            print '\n'
            
