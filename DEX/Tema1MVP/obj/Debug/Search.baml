   M S B A M L   `   `   `  ����C  ?Tema1MVP, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null#clr-namespace:Tema1MVPTema1MVP  5      #clr-namespace:Tema1MVPTema1MVP  5          Tema1MVP.Search   5      \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      (localclr-namespace:Tema1MVP     5      &ctxclr-namespace:Tema1MVP     5        N� Title$  Search��5
      $	��808��6   $
��1008��6#    � DataContext 5        Tema1MVP.WordVM  5   
   .��5      �  � RowDefinitions 5   
   �� 5      $��0* �6   �� 5      $
��386* �6   �� 5      $	��47* �6   �� 5      $
��376* �6    � ColumnDefinitions 5   
   �� 5      $��0* �6   �� 5      .+�5   
   �� 
���z���$
��Left=�6'   $	��748��6B   $��
0,68.5,0,0q�6O   
���z���$	��Top=�6x   $	��998��6�   $��1��6�   $��4��6�   �� 5   
   -   5        $��	LogoImage��5   �   $��2��6   $
��Left=�6$   $	��148��6?   $��323,127,0,0q�6L   $��2��6a   $	��Top=�6r   $	��340��6�   $��logo.PNG��6�   �� 5   
   -   5        $��	myTextBox��5   �   $��2��6   $
��Left=�6&   $��25��6A   $��
82,303,0,0q�6M   $��2��6a    �� TextWrapping$
 Wrap=�6r   $�� ��6�   $	��Top=�6�   $	��415��6�   6�   �� 5   
   -   5        $��	myListBox��5      $��2��6#   $
��Left=�67   $��87��6R   $��
82,328,0,0q�6^   $��3��6r   $	��Top=�6�   $	��415��6�    �� DisplayMemberPath$ MyWord��6�   $y�Hidden=�6�   �� 5   
   $��2��6   $
��Word��6$   $
��Left=�63   $��43��6N   $��
82,0.2,0,0q�6Z   $	��Top=�6n   $	��170��6�   $��23(�6�   $��SemiBold"�6�   $��3��6�   �� 5   
   $��2��6   $��Category��6$   $
��Left=�67   $��47��6R   $��80,87.2,0,0q�6^   $	��Top=�6s   $	��169��6�   $��23(�6�   $��SemiBold"�6�   $��3��6�   �� 5   
   $��2��6   $��Description��6$   $
��Left=�6:   $��44��6U   $��82,228.2,0,0q�6a   $	��Top=�6w   $	��170��6�   $��23(�6�   $��SemiBold"�6�   $��3��6�   �� 5    
   -   5         ��Name$
 word��5    �   $��2��6   $
��Left=�6&   $��47��6A   $��241,35.4,0,0q�6M   $
 Wrap=�6c   $	��Top=�6�   $	��256��6�   $��2��6�   $��2��6�   ��6w   ��  �� ElementName$ 	myListBox�� �� Path$ SelectedItem.MyWord�6�   �� 5!   
   -   5        $ description��5!   �   $��2��6   $
��Left=�6&   $	��149��6A   $��241,173.2,0,0q�6N   $
 Wrap=�6e   $	��Top=�6�   $	��256��6�   $��3��6�   ��6y   �� $ 	myListBox��$  SelectedItem.MyDescription�6�   �� 5"   
   -   5        	 ��Name$	 DefaultImage��5"   �   $��2��6   $
��Left=�6$   $	��336��6?   $��602,0.2,0,0q�6L   $	��Top=�6a   $	��316��6y   $��3��6�   ��6�   �� $ 	myListBox��$ SelectedItem.MyWordImage�6�   �� 5#   
   -   5        $ 	word_Copy��5#   �   $��2��6   $
��Left=�6&   $��47��6A   $��241,86.2,0,0q�6M   $
 Wrap=�6c   $	��Top=�6�   $	��256��6�   $��3��6�   ��6w   �� $ 	myListBox��$ SelectedItem.MyCategory�6�   �� 5$   
   -   5        $��myNewTextBox��5$   �   $��2��6   $
��Left=�6&   $��25��6A   $��602,303,0,0q�6M   $��2��6b   $
 Wrap=�6s   $	��Top=�6�   $	��317��6�   6�   5%      5&      