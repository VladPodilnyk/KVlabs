from .data_base import Order, Product, Stock, Client
from django import forms


class OrderForm(forms.Form):
    id = forms.IntegerField(label='ID')
    product_id = forms.CharField(label='ProductID')
    client_id = forms.CharField(label='ClientID')
    date_time = forms.DateTimeField(label='Date&Time')
    amount = forms.ImageField(label='Amount')


class StockForm(forms.Form):
    id = forms.IntegerField(label='ID')
    name = forms.CharField(label='Name', max_length=50)
    location = forms.CharField(label='Location', max_length=50)
    type = forms.CharField(label='Type', max_length=50)
    max_capacity = forms.ImageField(label='Capacity')


class ProductForm(forms.Form):
    id = forms.IntegerField(label='ID')
    name = forms.CharField(label='Name', max_length=50)
    type = forms.CharField(label='Type', max_length=50)
    cost = forms.IntegerField(label='Cost')
    num_of = forms.IntegerField(label='Amount')
    stock_id = forms.IntegerField(label='StockID')


class ClientForm(forms.Form):
    id = forms.IntegerField(label='ID')
    name = forms.CharField(label='Name', max_length=50)
    company = forms.CharField(label='Name', max_length=100)



