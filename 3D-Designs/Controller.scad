$fn = 50;
wall = 2;
tol = 0.5 ;

margin_bottom = 5;

B = 51;
H = 50;
L = 81;


box(); tekst();
//translate ([65, 0, 0]) bodemplaat();
//rotate ([0,0,90]) translate([100, - 90, 0]) deksel();


module tekst() {
    x_pos = 38;
    y_pos = 15;
    mirror([0, 180, 0]) {
        color("White") {
            rotate([90,0, -90]) {
                translate([x_pos , 14 + y_pos, -B - wall - 1])
                    linear_extrude(height=1.8, convexity=1) 
                    text("HW 40-B", size=10, font="Impact", halign="center", valign="center");
                translate([x_pos , y_pos, -B - wall - 1])
                    linear_extrude(height=1.8, convexity=1) 
                        text("Controller", size=10, font="Impact", halign="center", valign="center");
            }
        }
                    
        
    }
}

module box(bodemplaat = false) {
    difference () {
        minkowski() {
            cube([B, L, H], center = false);
            cylinder(r=wall ,h=1);
        }
        translate([0, 0, wall]) cube([B, L, H], center = false);
        usb_w = 8; usb_h = 4;
        translate([(B - usb_w) / 2 , -5, wall + 13]) color("silver") cube([usb_w, 10, usb_h]);
        usb_w2 = 15; usb_h2 = 10;
        translate([(B - usb_w2) / 2 , -11, wall + 13 - (usb_h2 - usb_h)/2]) cube([usb_w2, 10, usb_h2]);
        rotate([90,0, 0]) translate ([17/2 + 6, H - 0.5*17 - 5, -L]) holes_sensor();

        //kabeltje relay
        d_cord = 4.5;
        translate([- 16, 0, 12.5]) {
            translate([(B - d_cord)/2 + 0.5 * d_cord, d_cord , wall + d_cord/2]) rotate([90,0, 0]) cylinder(d = d_cord, h = 15);
        }
        if (!bodemplaat) {
            rotate([0, 90, 0]) translate([-35, 20, -1])
            grove_2_x_4();
        }

    }
}

module deksel () {
    difference() {
        union() {
            minkowski() {
                cube([B, L, wall], center = false);
                cylinder(r=wall ,h=1);
            }
            translate ([0, 0, wall]) cube([B, L, 1.5 * wall], center = false);
            
        }
        
        translate([B/2 - 10 , 25, 0.5]) rotate([0, 0, -90]) lightsensor();
        translate([B/2 + 10, 75, 1.5]) rotate([0, 0, 180]) grove_2_x_4();
        
    }

}

module lightsensor() {
    grove_x = 20;
    grove_y = 20;
    color("Silver")  {
        scale([1.03, 1.03, 1]) {
            difference() {
                cube([grove_x ,grove_y, 5]);
                rotate([180, 0, 90]) translate([grove_x/2, grove_y + 0.1, -6]) grove_cut_hole();
                rotate([180, 0, -90]) translate([-10, 0.1, -6]) grove_cut_hole();
            }
            translate([grove_x/2, 0, 0]) cylinder(h=5, r=2);
            translate([grove_x/2, grove_y, 0]) cylinder(h=5, r=2);
            // LED hole:
            translate([grove_x/2 - 1, .8 + grove_y/2, -7]) cylinder(d=6, h=10);
        }
    }
}

module grove_2_x_4() {
    grove_x = 20;
    grove_y = 40;
    color("Yellow")  {
        scale([1.02, 1.02, 1]) {
            cube([grove_x ,grove_y, 5]);
            translate([20, 10, 0]) cylinder(h=5, r=2);
            translate([0, 10, 0]) cylinder(h=5, r=2);
            translate([grove_x/2, grove_y, ]) cylinder(h=5, r=2);
            
        }
    }
}


module grove_ring() {
    difference() {
        color("Yellow") cylinder(h=5 + 0.2, r=2.5);
        translate([0, 0, -1]) cylinder(h=7, r=2);
    }
}

module grove_cut_hole() {
    difference() {
        translate([0, 0, 0]) cylinder(h=12, r=2);
        translate([-2, 0, -1]) cube([6, 20, 20]);
    }
}


module bodemplaat () {
    difference () {
        minkowski() {
            cube([B, L, 2 * wall], center = false);
            cylinder(r=2 * wall ,h=1);
        }
        translate([0,0,3.1])
        box(true);
        translate([5, 5, -3]) cylinder(d=3, h = 10);
        translate([5, 5, 2]) cylinder(d=6, h = 10);

        translate([B - 5, L - 5, -3]) cylinder(d=3, h = 10);
        translate([B - 5, L - 5, 1.5]) cylinder(d=6, h = 10);

        translate([B - 5, 5, -3]) cylinder(d=3, h = 10);
        translate([B - 5, 5, 1.5]) cylinder(d=6, h = 10);
        
        translate([5, L - 5, -3]) cylinder(d=3, h = 10);
        translate([5, L - 5, 1.5]) cylinder(d=6, h = 10);
        

    }
}


        
module holes_sensor()
{
    d = 16;
    margin = 1;
    cylinder(h=15, d=d + margin, center = true); 
    translate([6 + d + margin ,0,0]) cylinder(h=15, d=d + margin, center = true); 
       
 }