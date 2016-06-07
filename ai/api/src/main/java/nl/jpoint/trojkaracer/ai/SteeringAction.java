package nl.jpoint.trojkaracer.ai;

public final class SteeringAction {

    private final float steeringPosition;

    public SteeringAction(final float steeringPosition) {
        this.steeringPosition = steeringPosition;
    }

    /**
     * @return The desired steering position, as a number between -1 and +1, with 0 being exactly centered.
     * -1 is max right, +1 is max left.
     */
    public float getSteeringPosition() {
        return steeringPosition;
    }
}
