ense470-helicopter
==================

--- Milestone 1 ---

Redmine Wiki: http://ense.gelowitz.org/redmine/projects/ense470-2014-cook-vicenzino-weiwang/wiki

Karim's Bitbucket: https://bitbucket.org/naqvik/ense470-2014

S/W Requirements:

    - The goal is to create an obstacle course on a landscape of your
      choosing (a model file) that your helicopter will fly through.

      - You must have a minimum of three obstacles.  

      The user action shall be the keyboard and the mouse.  The two
      controls for the helicopter are

      - rotor speed, and
      - rotor tilt.  

    - Use the '1' and '2' keys to decrease/increase rotor speed.  The
      '0' key should be used to reduce the rotor speed to zero.  The
      '3' key should be used to set the rotor to "neutral mode" where
      the rotor force will be equal, in magnitude, to the force of
      gravity, and thus if the rotor tilt is zero, the force of
      gravity will be exactly balanced and helicopter will have zero
      vertical acceleration.
      
      Design the software to make it easy to change the
      specific keys used.

    - Use the mouse to tilt your rotor to a maximum of 15 degrees in
      any direction.  You do not have to animate the tilt or rotation
      of the rotor.  You should use the 'c' key to centre the rotor,
      that is, to set the rotor tilt to zero.

      - Hence, hitting the '3' key and the 'c' key will cause the
        helicopter to have no vertical acceleration, 

    - You must implement viscous air friction.  You'll have to do a
      bit of research to find an appropriate value for the coefficient
      of viscous friction, but the precise value is not really critical.

    - Horizontal acceleration/deceleration are achieved by tilting the rotor
      in the direction of the desired acceleration.

    - You can assume the ground is at Z=0, that is, the ground is an
      infinite flat plane.  The camera should be located
      some distance behind the tail of the helicopter at all times as
      you fly.  One thing to note is with this design the helicopter
      will be able to move in all directions, however it will always
      point in the same direction.


