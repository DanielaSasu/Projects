   M S B A M L   `   `   `  ����C  ?Tema2MVP, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null9!clr-namespace:Tema2MVP.ViewModelsTema2MVP.ViewModels  5   	       Tema2MVP.Views.MainWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   3local!clr-namespace:Tema2MVP.ViewModels     5   	     � Title$  Tema 2��5   	   $	��806��6   $��1191.2��6%    � 
ResizeMode$ NoResize=�65    � WindowStartupLocation$ CenterScreen=�6K    � DataContext 5	         Tema2MVP.ViewModels.GameVM  5
   
   .��5      � $
��Left=�6   $	��786��6&   $��
-3,-16,0,0q�63   $	��Top=�6G   $
��1353��6_   .+�5   
   �� -   5        $
��grid��5      $��Bottom=�6E   $	��670��6`   $��465,0,182,31q�6m   ��6#   �� *	GameBoard+��5      �� 5      .R�5      �� ��6#   �� ��5      �� 5      .R�5   "   ��  �� Orientation$ 
Horizontal=�6-   5      ��5      �� 5      .R�5   "   �� $��80��6)   $��80��64   $��2q�6@   ���#000000._�5   &   �� ��6-   �� *ClickCommand+��6O   �� *
SimpleCell+��5   *   �� 5   .   .R�5   2   �� $��UniformToFill=�6`   ��68   �� *SimpleCell.CellImage+6`   5   /   5   '   5    #   5!      5#      5$      5&      �� 5'   
   -   5        $��NEW GAME��5'      
�������
�������$��17(�6J   $
��Bold"�6X   $
��Left=�6j   $��63��6�   $��
84,298,0,0q�6�   $	��Top=�6�   $	��297��6�   6�   �� 5(   
   -   5        $��	SAVE GAME��5(      
�������
�������$��17(�6J   $
��Bold"�6X   $
��Left=�6j   $��63��6�   $��
84,385,0,0q�6�   $	��Top=�6�   $	��297��6�   6�   �� 5)   
   -   5        $��	LOAD GAME��5)      
�������
�������$��17(�6J   $
��Bold"�6X   $
��Left=�6j   $��63��6�   $��
84,475,0,0q�6�   $	��Top=�6�   $	��297��6�   6�   �� 5*   
   -   5        $��ABOUT��5*      
�������
�������$��17(�6F   $
��Bold"�6T   $
��Left=�6f   $��63��6�   $��
84,656,0,0q�6�   $	��Top=�6�   $	��297��6�   6�   �� 5+   
   -   5        $��
STATISTICS��5+      
�������
�������$��17(�6K   $
��Bold"�6Y   $
��Left=�6k   $��63��6�   $��
84,566,0,0q�6�   $	��Top=�6�   $	��297��6�   6�   �� 5,   
   $
��Left=�6   $	��188��6+   $��
122,85,0,0q�68   $	��Top=�6L   $	��224��6d   $[��UC:\Users\Dani\Desktop\Personal projects\Checkers\Tema2MVP\Tema2MVP\Resources\logo.JPG��6p   5-      5.      