$fn = 50;
wall = 2;
tol = 0.5 ;

margin_bottom = 5;

B = 51;
H = 15 + margin_bottom;
L = 62 + 25;


box();
paaltjes();
mkr1000_raiser();
//text();
translate ([65, 0, 0]) bodemplaat();
rotate ([0,0,90]) translate([100, - 90, 0]) deksel();

module text() {
    x_pos = -45;
    y_pos = 10;
    color("#ffffff") rotate([90,0, -90]) translate([x_pos , y_pos, 1])
            linear_extrude(height=1.8, convexity=1) 
                text("Rangesensor", size=10, font="Bitstream Vera Sans", halign="center", valign="center");
                
    mirror([0, 180, 0]) 
    color("#ffffff") rotate([90,0, -90]) translate([x_pos + 88 , y_pos, -B - wall - 1])
            linear_extrude(height=1.8, convexity=1) 
                text("HW 40-B", size=10, font="Bitstream Vera Sans", halign="center", valign="center");
}

module box() {
    difference () {
        difference () {
            minkowski() {
                cube([B, L, H], center = false);
                cylinder(r=wall ,h=1);
            }
            translate([0, 0, wall]) cube([B, L, H], center = false);
            usb_w = 8; usb_h = 4;
            translate([(B - usb_w) / 2 , -5, margin_bottom + 1.5]) color("silver") cube([usb_w, 10, usb_h]);
            usb_w2 = 15; usb_h2 = 10;
            translate([(B - usb_w2) / 2 , -11, 1.5 + margin_bottom - (usb_h2 - usb_h)/2]) cube([usb_w2, 10, usb_h2]);
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
        translate ([17/2 + 6, 17/2 + 4, 0]) holes_sensor();
        
    }

}

module bodemplaat () {
    difference () {
        minkowski() {
            cube([B, L, 2 * wall], center = false);
            cylinder(r=2 * wall ,h=1);
        }
        translate([0,0,3.1])
        box();
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


module paaltjes() {
    d = 2;

    color("Silver") translate([30, L - d - 1, tol]) paaltje(10, d);
    color("Silver") translate([30, L - d - 1 - 20, tol]) paaltje(10, d);
    color("Silver") translate([0, L - d - 1 - 10, tol]) paaltje(10, d);
}

module paaltje(h, d) {
    blokje_padding = 1;
    cube([d + blokje_padding, d + blokje_padding, margin_bottom - tol], center = false) ;
    translate([0.5 * d + 0.5 * blokje_padding, 0.5 * d + 0.5 * blokje_padding, tol]) cylinder(d = d, h = h - tol, center = false);

}

module mkr1000_raiser() {
    //raisers for MKR1000:
    color("Silver") translate([- tol, 0, tol]) cube([B + 2 * tol, 10, margin_bottom - tol]);
    color("Silver") translate([B / 2 + tol, 52, tol]) cube([B / 2, 10, margin_bottom - tol]);

}
        
module holes_sensor()
{
    d = 16;
    margin = 1;
    cylinder(h=15, d=d + margin, center = true); 
    translate([6 + d + margin ,0,0]) cylinder(h=15, d=d + margin, center = true); 
       
 }