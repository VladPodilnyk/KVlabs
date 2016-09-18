class View:
    @staticmethod
    def data_base_menu():
        print 'Data base menu\n--------------'
        print 'Choose one of the following items:'
        print '1) Cinemas menu'
        print '2) Sessions menu'
        print '3) Exit'

    @staticmethod
    def display(lst):
        for element in lst:
            print '\n'.join(map(lambda key: key + ' : ' + str(element[key]), element.keys()))
            print '\n'


    @staticmethod
    def cinemas_menu():
        print 'Cinemas menu'
        print '1) Add cinema\n2) Delete cinema\n3) Update\n4) Display cinema after specific time\n5) Display\n6) Back\n'

    @staticmethod
    def sessions_menu():
        print 'Sessions menu'
        print '1) Add session\n2) Delete session\n3) Update\n4) Display\n5) Back\n'

    @staticmethod
    def cinemas_update_menu():
        print 'Cinema update menu'
        print '1) Name\n2) Street\n3) Back\n'

    @staticmethod
    def sessions_update_menu():
        print 'Session update menu'
        print '1) Name\n2) Time\n3) Cost\n4) Back\n'

    @staticmethod
    def success_message(message):
        print message + '\n'

    @staticmethod
    def error_message(message):
        print '[ERROR]: ' + message + '\n'
