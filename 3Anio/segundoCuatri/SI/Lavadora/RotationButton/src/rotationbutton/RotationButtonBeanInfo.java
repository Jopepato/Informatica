/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package rotationbutton;

import java.awt.Image;
import java.beans.*;

public class RotationButtonBeanInfo extends SimpleBeanInfo{
     Image icon;
     Image icon32;
     Image iconM;
     Image icon32M;
     
     public RotationButtonBeanInfo(){
         icon = loadImage("/icon/jp16c.gif");
         icon32 = loadImage("/icon/jp32c.gif");
         iconM = loadImage("/icon/jp16m.gif");
         icon32M = loadImage("/icon/jp32m.gif");
     }
     
     @Override
     public Image getIcon(int i){
         switch(i)
         {
         case 1:
             return icon;
 
         case 2:
             return icon32;
 
         case 3:
             return iconM;
 
         case 4:
             return icon32M;
         }
         return null;
     }
 }